// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"), //검
	Axe UMETA(DisplayName = "Axe"), //도끼

	Max UMETA(DisplayName = "Max")
};
