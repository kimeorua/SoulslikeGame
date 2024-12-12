// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingMagnitudeCalculation.h"
#include "SoulslikeAttributeSetBase.h"

UHealingMagnitudeCalculation::UHealingMagnitudeCalculation()
{
	TalentDef.AttributeToCapture = USoulslikeAttributeSetBase::GetTalentAttribute();
	TalentDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	TalentDef.bSnapshot = false;

	MaxStatDef.AttributeToCapture = USoulslikeAttributeSetBase::GetMaxStatAttribute();
	MaxStatDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStatDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(TalentDef);
	RelevantAttributesToCapture.Add(MaxStatDef);
}

float UHealingMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* Source = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* Target = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Source;
	EvaluateParameters.TargetTags = Target;

	float Talent = 0.0f;
	GetCapturedAttributeMagnitude(TalentDef, Spec, EvaluateParameters, Talent);

	float MaxStat = 0.0f;
	GetCapturedAttributeMagnitude(MaxStatDef, Spec, EvaluateParameters, MaxStat);

	Talent = FMath::Clamp(Talent, 0.0f, MaxStat);

	return Base + Talent;
}