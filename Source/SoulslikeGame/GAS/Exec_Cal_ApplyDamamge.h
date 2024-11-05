// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Exec_Cal_ApplyDamamge.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UExec_Cal_ApplyDamamge : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
	UExec_Cal_ApplyDamamge();

	virtual void Execute_Implementation
	(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float BaseCriticalChance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float BaseCriticalRate = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float StrengthCap = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float DamageRateMin = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float DamageRateMax = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float ManaGain = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float SPDawnRate = 1.0f;
};
