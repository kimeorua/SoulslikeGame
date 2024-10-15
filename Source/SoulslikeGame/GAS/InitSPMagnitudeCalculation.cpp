// Fill out your copyright notice in the Description page of Project Settings.


#include "InitSPMagnitudeCalculation.h"
#include "SoulslikeAttributeSetBase.h"

UInitSPMagnitudeCalculation::UInitSPMagnitudeCalculation()
{
	WillDef.AttributeToCapture = USoulslikeAttributeSetBase::GetWillAttribute();
	WillDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	WillDef.bSnapshot = false;

	MaxStatDef.AttributeToCapture = USoulslikeAttributeSetBase::GetMaxStatAttribute();
	MaxStatDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStatDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(WillDef);
	RelevantAttributesToCapture.Add(MaxStatDef);
}

float UInitSPMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* Source = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* Target = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Source;
	EvaluateParameters.TargetTags = Target;

	float Will = 0.0f;
	GetCapturedAttributeMagnitude(WillDef, Spec, EvaluateParameters, Will);

	float MaxStat = 0.0f;
	GetCapturedAttributeMagnitude(MaxStatDef, Spec, EvaluateParameters, MaxStat);

	Will = FMath::Clamp(Will, 0.0f, MaxStat);

	return Base + (Will * Rate);
}
