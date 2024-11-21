// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_Cal_Guard_SPDawn.h"
#include "../GAS/SoulslikeAttributeSetBase.h"
#include "../Character/BaseCharacter.h"

struct SPDawnCature
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(SP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Will);

	SPDawnCature()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, SP, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Will, Target, false);
	}
};

static SPDawnCature& GetSPDawnCature()
{
	static SPDawnCature SPDawnCature;
	return SPDawnCature;
}


UExec_Cal_Guard_SPDawn::UExec_Cal_Guard_SPDawn()
{
	RelevantAttributesToCapture.Add(GetSPDawnCature().SPDef);
	RelevantAttributesToCapture.Add(GetSPDawnCature().WillDef);
}

void UExec_Cal_Guard_SPDawn::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const
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

	float SP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().SPDef, EvaluateParameters, SP);

	float Will = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetSPDawnCature().WillDef, EvaluateParameters, Will);

	float SPDawn;

	if (Will / 10 < 1)
	{
		SPDawn = BaseSPDawn;
	}
	else
	{
		SPDawn = BaseSPDawn - (Will / 10);
	}

	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetSPDawnCature().SPProperty, EGameplayModOp::Additive, -SPDawn));
}
