// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Components/LockOnComponent.h"
#include "../Components/WeaponComponent.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "../Weapons/Weapon.h"
#include "../DataAsset/WeaponDataAsset.h"

AEnemyCharacter::AEnemyCharacter()
{
	LockOnColliison = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LockOnCollision"));
	LockOnColliison->SetupAttachment(RootComponent);
	LockOnColliison->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	LockOnColliison->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LockOnColliison->SetCapsuleSize(0.1f, 0.1f);

	LockOnUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnUI"));
	LockOnUI->SetupAttachment(LockOnColliison);
	LockOnUI->bHiddenInGame = true;
	LockOnUI->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemyCharacter::WeaponSetting()
{
	GetWeaponComponent()->WeaponSelect(Type);

	AbilityActivateWithTag("Action.Equip");
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponSetting();
}

void AEnemyCharacter::LockOnUI_On_Off(bool OnOff)
{
	LockOnUI->bHiddenInGame = !OnOff;
}

void AEnemyCharacter::GuardBreak()
{
	Super::GuardBreak();
}
