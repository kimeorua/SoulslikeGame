// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_Cal_GuardParry.h"

#include "../GAS/SoulslikeAttributeSetBase.h"
#include "../Character/BaseCharacter.h"

struct SPDawnCature
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxSP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Will);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);

	SPDawnCature()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxSP, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, SP, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Will, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Strength, Target, false);
	}
};

static SPDawnCature& GetSPDawnCature()
{
	static SPDawnCature SPDawnCature;
	return SPDawnCature;
}


UExec_Cal_GuardParry::UExec_Cal_GuardParry()
{
	RelevantAttributesToCapture.Add(GetSPDawnCature().MaxSPDef);
	RelevantAttributesToCapture.Add(GetSPDawnCature().SPDef);
	RelevantAttributesToCapture.Add(GetSPDawnCature().WillDef);
	RelevantAttributesToCapture.Add(GetSPDawnCature().StrengthDef);
}

void UExec_Cal_GuardParry::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const
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

	float MaxSP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().MaxSPDef, EvaluateParameters, MaxSP);

	float SP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().SPDef, EvaluateParameters, SP);

	float Will = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().WillDef, EvaluateParameters, Will);

	float Strength = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().StrengthDef, EvaluateParameters, Strength);

	float SPDawn = 0.0f;
	
	if (MaxSP > 0)
	{
		SPDawn = MaxSP / Rate;
	}

	SPDawn -= Will / 10.0f;

	SPDawn += Strength / 10.0f;

	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(SPDawnCature().SPProperty, EGameplayModOp::Additive, -SPDawn));
}
