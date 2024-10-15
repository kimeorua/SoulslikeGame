// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "InitSPMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UInitSPMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UInitSPMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const override;

private:
	FGameplayEffectAttributeCaptureDefinition WillDef;
	FGameplayEffectAttributeCaptureDefinition MaxStatDef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Rate = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Base = 50.0f;
};
