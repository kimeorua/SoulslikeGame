// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"), //검
	Axe UMETA(DisplayName = "Axe"), //도끼

	Max UMETA(DisplayName = "Max")
};

USTRUCT(BlueprintType)
struct FEquipMontages
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	class UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	class UAnimMontage* UnequipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	float PlayRate = 1.0f;
};

USTRUCT(BlueprintType)
struct FCurrentWeaponInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AWeapon* EquipWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UWeaponDataAsset* EquipWeaponDataAsset;
};