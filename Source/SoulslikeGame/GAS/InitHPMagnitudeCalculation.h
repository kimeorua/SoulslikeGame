// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "InitHPMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UInitHPMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
	UInitHPMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const override;

	FGameplayEffectAttributeCaptureDefinition HealthDef;
	FGameplayEffectAttributeCaptureDefinition MaxStatDef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Rate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Base = 100.0f;

	/** Attributes to capture that are relevant to the calculation */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	const TArray<FGameplayEffectAttributeCaptureDefinition> RelevantAttributesToCapturePtr;
};
