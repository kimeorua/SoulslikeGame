// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKEGAME_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> LockOnClass;

	class ABaseCharacter* LockActor;
	class ABaseCharacter* Owner;

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

	TArray<ABaseCharacter>TraceForTarget();

	UFUNCTION(BlueprintCallable)
	void TriggerTargetLockOn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
