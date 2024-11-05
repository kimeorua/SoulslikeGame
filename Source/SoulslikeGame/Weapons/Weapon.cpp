// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Enums.h"
#include "../Character/BaseCharacter.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Attach(FName Socket)
{
	Super::Attach(Socket);
}

TTuple<bool, ABaseCharacter*, FVector, FVector> AWeapon::TraceOn(FCollisionData CollisionData)
{
	bool Succes = false;
	FVector StartLocation = Mesh->GetSocketLocation(CollisionData.CollisionStartSocketName);
	FVector EndLocation = Mesh->GetSocketLocation(CollisionData.CollisionEndSocketName);

	FVector Size = FVector(CollisionData.Size / 2, CollisionData.Size / 2, CollisionData.Size);

	// 충돌 검사할 오브젝트 타입
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));

	// 충돌 결과
	FHitResult HitResult;

	// 무시할 객체
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(GetOwner()));

	switch (CollisionData.TraceType)
	{
	case ETraceType::None:
		break;

	case ETraceType::Sphere:
		Succes = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, CollisionData.Size, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
		break;

	case ETraceType::Box:
		Succes = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), StartLocation, EndLocation, Size, GetActorRotation(), ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
		break;

	case ETraceType::Max:
		break;

	default:
		break;
	}
	return MakeTuple(Succes, Cast<ABaseCharacter>(HitResult.GetActor()), GetOwner()->GetActorLocation(), HitResult.ImpactPoint);
}