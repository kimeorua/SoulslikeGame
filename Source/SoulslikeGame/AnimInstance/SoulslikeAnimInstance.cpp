// Fill out your copyright notice in the Description page of Project Settings.

#include "SoulslikeAnimInstance.h"
#include "SoulslikeGame/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "../Components/LockOnComponent.h"
#include "../Components/WeaponComponent.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"

USoulslikeAnimInstance::USoulslikeAnimInstance()
{
	MovementComponent = nullptr;
	WeaponComponent = nullptr;
	GASComponent = nullptr;
	Character = nullptr;
}

void USoulslikeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(Character))
	{
		SettingVlaue();
	}
	else
	{
		Character = Cast<ABaseCharacter>(TryGetPawnOwner());
		if (IsValid(Character))
		{
			MovementComponent = Character->GetCharacterMovement();
			GASComponent = Character->GetAbilitySystemComponent();
			WeaponComponent = Character->GetWeaponComponent();
		}
		SettingVlaue();
	}
}

void USoulslikeAnimInstance::SettingVlaue()
{
	if (IsValid(MovementComponent))
	{
		Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		FRotator Rot = FRotator(0.0f, Character->GetActorRotation().Yaw, 0);
		Direction = UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, Rot);
		IsAccelerating = UKismetMathLibrary::VSize(MovementComponent->GetCurrentAcceleration()) > 0 ? true : false;
		IsAir = MovementComponent->IsFalling();

		if (GASComponent)
		{
			IsLockOn = GASComponent->GetTagCount(FGameplayTag::RequestGameplayTag(FName("State.UseLockOn"))) > 0 ? true : false;
			IsAirAttck = GASComponent->GetTagCount(FGameplayTag::RequestGameplayTag(FName("Action.Attack.Jump"))) > 0 ? true : false;
		}
		if (IsValid(WeaponComponent))
		{
			if (IsValid(WeaponComponent->GetCurrentWeaponInfo().DataAsset))
			{
				WeaponType = WeaponComponent->GetCurrentWeaponInfo().DataAsset->GetWeaponType();
			}
			else
			{
				WeaponType = EWeaponType::None;
			}
		}
	}
}
