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
	// 무기 블루 프린트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> WeaponClass;

	// 무기 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class", meta = (AllowPrivateAccess = "true"))
	EWeaponType Type;

	// 장착될 소켓
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FName EquipSokcet;

	// 장착 중이 아닐 시 부착될 소켓
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FName UnequipSokcet;

	// 장착 및 장착 해제 몽타주 및 재생 속도 구조체
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip", meta = (AllowPrivateAccess = "true"))
	FEquipMontages EquipMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FAttackMontages AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack | Collision", meta = (AllowPrivateAccess = "true"))
	FCollisionData CollisionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack | Damage", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

public:
	FORCEINLINE TSubclassOf<class AWeapon> GetWeaponClass() const{ return WeaponClass; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetEquipSokcet() const { return EquipSokcet; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetUnequipSokcet() const { return UnequipSokcet; }

	FORCEINLINE EWeaponType GetWeaponType() const { return Type; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FEquipMontages GetEquipMontages() const { return EquipMontages; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FAttackMontages GetAttackMontages() const { return AttackMontages; }

	FORCEINLINE FCollisionData GetCollisionData() const { return CollisionData; }

	FORCEINLINE float GetBaseDamage() const { return BaseDamage; }
};
