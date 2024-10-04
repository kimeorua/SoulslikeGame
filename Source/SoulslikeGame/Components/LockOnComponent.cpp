// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
#include "../Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LockOnActor = nullptr;
	Owner = nullptr;
	IsLockOn = false;
}

ABaseCharacter* ULockOnComponent::TraceForTarget()
{
	FVector Location = Owner->GetActorLocation();

	// 충돌 검사할 오브젝트 타입
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	// 충돌 결과
	FHitResult HitResult;

	// 무시할 객체
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(Owner));
	
	// 반환할 락온 대상
	ABaseCharacter* HitActor;

	bool Succes = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Location, Location,  LockOnRadius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (Succes)
	{
		HitActor = Cast<ABaseCharacter>(HitResult.GetActor());
		return HitActor;
	}
	else
	{
		return nullptr;
	}
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Cast<APlayerCharacter>(GetOwner()))
	{
		Owner = Cast<APlayerCharacter>(GetOwner());
	}
}

bool ULockOnComponent::CheackTarget(ABaseCharacter* Target)
{
	//트레이스 타입
	TEnumAsByte<ETraceTypeQuery>TraceType;
	TraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);

	//무시할 객체 배열
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(Owner));
	
	// 충돌 결과
	FHitResult HitResult;
	bool Trace = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Owner->GetCamera()->GetComponentLocation(), Target->GetActorLocation(), TraceType, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	if (!Trace)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ULockOnComponent::TriggerTargetLockOn()
{
	if (IsLockOn)
	{
		StopTargetLockOn();
	}
	else if (!IsLockOn)
	{
		if (IsValid((TraceForTarget())))
		{
			if (CheackTarget(TraceForTarget()))
			{
				LockOnActor = TraceForTarget();
				//타이머를 통해, 자연스러운 카메라 무브
				GetWorld()->GetTimerManager().SetTimer(LockOnHandle, this, &ULockOnComponent::TargetLockOn, GetWorld()->GetDeltaSeconds(), true);
			}
		}
	}
	
}

void ULockOnComponent::TargetLockOn()
{
	float Dis = UKismetMathLibrary::Vector_Distance(Owner->GetActorLocation(), LockOnActor->GetActorLocation());

	if (Dis > LockOnRadius)
	{
		StopTargetLockOn();
	}
	else
	{
		FRotator Rot = UKismetMathLibrary::RInterpTo(Owner->GetController()->GetControlRotation(), GetLockOnCameraRotation(), 0.01f, 10.0f);
		FRotator CameraRot = FRotator(Rot.Pitch, Rot.Yaw, Owner->GetController()->GetControlRotation().Roll);
		Owner->GetController()->SetControlRotation(CameraRot);

		Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
		Owner->bUseControllerRotationYaw = true;
		IsLockOn = true;

		if (Owner->GetAbilitySystemComponent()->GetTagCount((FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")))) <= 0)
		{
			Owner->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")));
		}
	}
}

void ULockOnComponent::StopTargetLockOn()
{
	GetWorld()->GetTimerManager().ClearTimer(LockOnHandle);
	LockOnActor = nullptr;

	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	Owner->bUseControllerRotationYaw = false;
	IsLockOn = false;

	if (Owner->GetAbilitySystemComponent()->GetTagCount((FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")))) > 0)
	{
		Owner->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")));
	}
}

FRotator ULockOnComponent::GetLockOnCameraRotation()
{
	float Value = UKismetMathLibrary::Vector_Distance(Owner->GetActorLocation(), LockOnActor->GetActorLocation());
	FVector Vec = FVector(LockOnActor->GetActorLocation().X, LockOnActor->GetActorLocation().Y, LockOnActor->GetActorLocation().Z - Value / 2.0f);

	return UKismetMathLibrary::FindLookAtRotation(Owner->GetCamera()->GetComponentLocation(), Vec);
}

