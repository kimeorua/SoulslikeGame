// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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

public:
	TSubclassOf<class AWeapon> GetWeaponClass() const{ return WeaponClass; }
	
};
