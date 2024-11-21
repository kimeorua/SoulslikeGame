// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_Cal_ExecutionDamage.h"
#include "../GAS/SoulslikeAttributeSetBase.h"
#include "../Character/BaseCharacter.h"

struct ExecutionCature
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);

	ExecutionCature()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxHP, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, HP, Target, false);
	}
};

static ExecutionCature& GetExecutionCature()
{
	static ExecutionCature ExecutionCature;
	return ExecutionCature;
}

UExec_Cal_ExecutionDamage::UExec_Cal_ExecutionDamage()
{
	RelevantAttributesToCapture.Add(GetExecutionCature().MaxHPDef);
	RelevantAttributesToCapture.Add(GetExecutionCature().HPDef);
}

void UExec_Cal_ExecutionDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const
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

	float Damage = 0.0f;

	float MaxHP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(ExecutionCature().MaxHPDef, EvaluateParameters, MaxHP);

	float HP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(ExecutionCature().HPDef, EvaluateParameters, HP);

	Damage = MaxHP * Rate;

	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetExecutionCature().HPProperty, EGameplayModOp::Additive, -Damage));
}
