// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossRoom.generated.h"

UCLASS()
class SOULSLIKEGAME_API ABossRoom : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Boss Room", meta = (AllowPrivateAccess = "true"))
	class AEnemyCharacter* Boss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss Room", meta = (AllowPrivateAccess = "true"))
	bool IsActivate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss Room", meta = (AllowPrivateAccess = "true"))
	FVector Size;

	FTimerHandle TimerHandle;

	class APlayerCharacter* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABossRoom();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateCollision();

};
