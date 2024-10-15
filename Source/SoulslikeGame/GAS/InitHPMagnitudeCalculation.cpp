// Fill out your copyright notice in the Description page of Project Settings.


#include "InitHPMagnitudeCalculation.h"
#include "SoulslikeAttributeSetBase.h"

UInitHPMagnitudeCalculation::UInitHPMagnitudeCalculation()
{
	HealthDef.AttributeToCapture = USoulslikeAttributeSetBase::GetHealthAttribute();
	HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HealthDef.bSnapshot = false;

	MaxStatDef.AttributeToCapture = USoulslikeAttributeSetBase::GetMaxStatAttribute();
	MaxStatDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStatDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(MaxStatDef);
}

float UInitHPMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* Source = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* Target = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Source;
	EvaluateParameters.TargetTags = Target;

	float Health = 0.0f;
	GetCapturedAttributeMagnitude(HealthDef, Spec, EvaluateParameters, Health);

	float MaxStat = 0.0f;
	GetCapturedAttributeMagnitude(MaxStatDef, Spec, EvaluateParameters, MaxStat);

	Health = FMath::Clamp(Health, 0.0f, MaxStat);

	return Base + (Health * Rate);
}
