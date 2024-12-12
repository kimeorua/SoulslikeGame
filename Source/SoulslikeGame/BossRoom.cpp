// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRoom.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../SoulslikeGame/Character/EnemyCharacter.h"
#include "../SoulslikeGame/Character/PlayerCharacter.h"

// Sets default values
ABossRoom::ABossRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Boss = nullptr;

}

// Called when the game starts or when spawned
void ABossRoom::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]() {ActivateCollision(); }), 1.0f, true);

}

// Called every frame
void ABossRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossRoom::ActivateCollision()
{
	if (IsActivate)
	{
		// 충돌 검사할 오브젝트 타입
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));

		// 충돌 결과
		FHitResult HitResult;

		// 무시할 객체
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(Cast<AActor>(Boss));

		bool Succes = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation(), Size, GetActorRotation(), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		if (Succes)
		{
			Player = Cast<APlayerCharacter>(HitResult.GetActor());

			if (IsValid(Player))
			{
				Player->SetBoss(Boss);

				GetWorldTimerManager().ClearTimer(TimerHandle);
				IsActivate = false;
			}
		}
	}
}