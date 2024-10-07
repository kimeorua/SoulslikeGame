// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShieldDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UShieldDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AShield> ShieldClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FName EquipSokcet;

public:
	FORCEINLINE TSubclassOf<class AShield> GetShieldClass() const { return ShieldClass; }
	FORCEINLINE FName GetEquipSokcet() const { return EquipSokcet; }
};
