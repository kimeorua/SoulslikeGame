// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SoluslikeAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API USoluslikeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool StartupEffectApplied = false;
};
