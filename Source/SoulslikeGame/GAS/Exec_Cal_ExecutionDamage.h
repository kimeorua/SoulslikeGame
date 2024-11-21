// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Exec_Cal_ExecutionDamage.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UExec_Cal_ExecutionDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UExec_Cal_ExecutionDamage();

	virtual void Execute_Implementation
	(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Value", meta = (AllowPrivateAccess = "true"))
	float Rate = 0.1f;
};
