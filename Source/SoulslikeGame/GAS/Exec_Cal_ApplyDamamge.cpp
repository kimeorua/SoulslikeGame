// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_Cal_ApplyDamamge.h"
#include "../GAS/SoulslikeAttributeSetBase.h"
#include "../Character/BaseCharacter.h"

struct DamageCature
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SP);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Concentration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStat);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Mana);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxMana);

	DamageCature()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, HP, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, SP, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Concentration, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxStat, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Mana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxMana, Source, false);
	}
};

static DamageCature& GetDamageCature()
{
	static DamageCature DamageCature;
	return DamageCature;
}

UExec_Cal_ApplyDamamge::UExec_Cal_ApplyDamamge()
{
	RelevantAttributesToCapture.Add(GetDamageCature().HPDef);
	RelevantAttributesToCapture.Add(GetDamageCature().SPDef);

	RelevantAttributesToCapture.Add(GetDamageCature().StrengthDef);
	RelevantAttributesToCapture.Add(GetDamageCature().ConcentrationDef);
	RelevantAttributesToCapture.Add(GetDamageCature().MaxStatDef);

	RelevantAttributesToCapture.Add(GetDamageCature().ManaDef);
	RelevantAttributesToCapture.Add(GetDamageCature().MaxManaDef);
}

void UExec_Cal_ApplyDamamge::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParms.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParms.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParms.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float HP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().HPDef, EvaluateParameters, HP);

	float SP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().SPDef, EvaluateParameters, SP);

	float Strength = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().StrengthDef, EvaluateParameters, Strength);

	float Concentration = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().ConcentrationDef, EvaluateParameters, Concentration);

	float MaxStat = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().MaxStatDef, EvaluateParameters, MaxStat);

	float Mana = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().ManaDef, EvaluateParameters, Mana);

	float MaxMana = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().MaxManaDef, EvaluateParameters, MaxMana);

	float CriticalPersent = BaseCriticalChance + FMath::Clamp(Concentration, 0.0f, MaxStat);

	float CriticalRate = BaseCriticalRate + FMath::Clamp(Concentration, 0.0f, MaxStat) * 0.02f;

	float WeaponBaseDamage = Cast<ABaseCharacter>(SourceActor)->GetWeaponBaseDamage();

	float Damage = 0.0f;

	if (Strength >= StrengthCap)
	{
		Damage = WeaponBaseDamage + (((StrengthCap - 1) * DamageRateMax) + (FMath::Clamp(Strength, 0.0f, MaxStat) - (StrengthCap - 1)) * DamageRateMin);
	}
	else
	{
		Damage = WeaponBaseDamage + FMath::Clamp(Strength, 0.0f, MaxStat) * DamageRateMax;
	}

	float Random = FMath::RandRange(0, 100);

	float TargetHPDawn;
	float SourceManaUp = ManaGain;

	if (Random <= CriticalPersent)
	{
		TargetHPDawn = FMath::CeilToInt(Damage * CriticalRate);
	}
	else
	{
		TargetHPDawn = FMath::CeilToInt(Damage);
	}

	if (Mana + SourceManaUp >= MaxMana)
	{
		SourceAbilitySystemComponent->ApplyModToAttribute(USoulslikeAttributeSetBase::GetManaAttribute(), EGameplayModOp::Override, MaxMana);
	}
	else
	{
		SourceAbilitySystemComponent->ApplyModToAttribute(USoulslikeAttributeSetBase::GetManaAttribute(), EGameplayModOp::Additive, SourceManaUp);
	}

	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCature().HPProperty, EGameplayModOp::Additive, -TargetHPDawn));
	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCature().SPProperty, EGameplayModOp::Additive, -TargetHPDawn * SPDawnRate));
}