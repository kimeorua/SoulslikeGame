// Fill out your copyright notice in the Description page of Project Settings.

#include "SoulslikeAnimInstance.h"
#include "SoulslikeGame/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "../Components/LockOnComponent.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"

USoulslikeAnimInstance::USoulslikeAnimInstance()
{
	MovementComponent = nullptr;
	GASComponent = nullptr;
	Character = nullptr;
}

void USoulslikeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
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
		}
	}
}
