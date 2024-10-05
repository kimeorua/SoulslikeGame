// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Enums.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class", meta = (AllowPrivateAccess = "true"))
	EWeaponType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FName EquipSokcet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FName UnequipSokcet;

public:
	FORCEINLINE TSubclassOf<class AWeapon> GetWeaponClass() const{ return WeaponClass; }
	FORCEINLINE FName GetEquipSokcet() const { return EquipSokcet; }
	FORCEINLINE FName GetUnequipSokcet() const { return UnequipSokcet; }
	FORCEINLINE EWeaponType GetWeaponType() const { return Type; }
};
