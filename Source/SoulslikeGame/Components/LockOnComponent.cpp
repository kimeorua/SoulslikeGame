// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
#include "../Character/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LockActor = nullptr;
	Owner = nullptr;
}

TArray<ABaseCharacter> ULockOnComponent::TraceForTarget()
{
	FVector Location = Owner->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(Owner));
	
	bool Succes = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Location, Location,  LockOnRadius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);

	if (Succes)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hi"));
	}

	return TArray<ABaseCharacter>();
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ABaseCharacter>(GetOwner());
	
}

void ULockOnComponent::TriggerTargetLockOn()
{
	TraceForTarget();
}

