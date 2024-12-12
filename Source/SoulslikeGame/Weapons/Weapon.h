// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop.h"
#include "../Enums.h"
#include "Weapon.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API AWeapon : public AProp
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(Category = "Particle", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailParticle;

public:
	AWeapon();

	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }

	virtual void BeginPlay() override;

	virtual void Attach(FName Socket)override;

	virtual TTuple<bool, ABaseCharacter*, FVector, FVector> TraceOn(FCollisionData CollisionData);
};
