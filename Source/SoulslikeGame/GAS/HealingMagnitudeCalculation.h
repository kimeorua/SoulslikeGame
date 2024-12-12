// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HealingMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UHealingMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UHealingMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const override;

private:
	FGameplayEffectAttributeCaptureDefinition TalentDef;
	FGameplayEffectAttributeCaptureDefinition MaxStatDef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Base = 30.0f;
};
