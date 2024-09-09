// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USoluslikeAbilitySystemComponent;

UCLASS()
class SOULSLIKEGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	//---------------------변수----------------------------//
private:
	// GameplayAbilitySystemComponent 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS | Component", meta = (AllowPrivateAccess = "true"))
	USoluslikeAbilitySystemComponent* SoluslikeGASCompoent;
	

	//----------------------함수-------------------------//
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
