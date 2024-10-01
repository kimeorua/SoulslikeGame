// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	const class USoulslikeAttributeSetBase* AttributeSetVar;

	//기본 HP SP Mana 적용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf <class UGameplayEffect >> InitEffects;

	//게임 시작시 사용 가능한 능력들(공격, 스킬 사용, 회복 사용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LockOnCollision", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* LockOnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement | Speed", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement | Speed", meta = (AllowPrivateAccess = "true"))
	float MinSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement | LockOn", meta = (AllowPrivateAccess = "true"))
	bool IsLockOn;

private:

	/// <summary>
	/// 기본 GameplayEffect 적용(HP, SP, Mana 적용)
	/// </summary>
	void Initalize();

	/// <summary>
	/// DefaultAbility적용
	/// </summary>
	void initalizeAbilities();

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

	/// <summary>
	/// GameplayAbility 추가 (단일)
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void GiveAbilitySingle(TSubclassOf<class UGameplayAbility> AbilityToGet, int32 AbilityLevel);

	/// <summary>
	///  GameplayAbility 추가 (복수)
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void GiveAbilityMulity(TArray<TSubclassOf<class UGameplayAbility>> AddedAbilities);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USoluslikeAbilitySystemComponent* GetAbilitySystemComponent() const { return SoulslikeGASCompoent; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxSpeed() const { return MaxSpeed; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMinSpeed() const { return MinSpeed; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
