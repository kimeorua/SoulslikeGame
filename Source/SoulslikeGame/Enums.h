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

UENUM(BlueprintType)
enum class ETraceType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Sphere UMETA(DisplayName = "Sphere"), // 캡슐
	Box UMETA(DisplayName = "Box"), // 박스

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
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	class UWeaponDataAsset* DataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	class AWeapon* Weapon;
};

USTRUCT(BlueprintType)
struct FAttackMontages
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	TArray <class UAnimMontage*> AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equips")
	float PlayRate = 1.0f;
};

USTRUCT(BlueprintType)
struct FCollisionData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	ETraceType TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	float Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	FName CollisionStartSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	FName CollisionEndSocketName;
};