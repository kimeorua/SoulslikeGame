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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Component", meta = (AllowPrivateAccess = "true"))
	USoluslikeAbilitySystemComponent* SoulslikeGASCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	const class USoulslikeAttributeSetBase* AttributeSetVar;
	

	//----------------------함수-------------------------//
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// <summary>
	/// 빙의 시 호출
	/// </summary>
	virtual void PossessedBy(AController* NewController) override;

	/// <summary>
	/// 플레이어 스태이트 변경
	/// </summary>
	virtual void OnRep_PlayerState() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
