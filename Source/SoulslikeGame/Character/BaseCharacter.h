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

	// 어트리뷰트 값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	const class USoulslikeAttributeSetBase* AttributeSetVar;

	//기본 HP SP Mana 적용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf <class UGameplayEffect >> InitEffects;

	//게임 시작시 사용 가능한 능력들(공격, 스킬 사용, 회복 사용)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS | Attribute", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbility;

	//무기 및 방패 제어용 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* WeaponComponent;

	// 전투 용 콜리전
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combet Collision", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CombetColliison;

	// 최대 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement | Speed", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed;

	// 최소 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement | Speed", meta = (AllowPrivateAccess = "true"))
	float MinSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit Montage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*>HitMontage;

	int HitIndex;

	FVector HitPoint;

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

	/// <summary>
	/// 어빌리티 시스템 컴포넌트 반환
	/// </summary>
	/// <returns>어빌리티 시스템 컴포넌트</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE USoluslikeAbilitySystemComponent* GetAbilitySystemComponent() const { return SoulslikeGASCompoent; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; };

	/// <summary>
	/// 최대 속도 반환
	/// </summary>
	/// <returns>최대 속도</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxSpeed() const { return MaxSpeed; };

	/// <summary>
	/// 최소 속도 반환
	/// </summary>
	/// <returns>최소 속도</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMinSpeed() const { return MinSpeed; };

	/// <summary>
	/// 무기 장착 Ability 작동
	/// </summary>
	virtual void Equip();

	/// <summary>
	/// 무기 장착 해제 Ability 작동
	/// </summary>
	virtual void Unequip(bool PlayAnim);

	/// <summary>
	///  Tag 를 변수로 어빌리티 작동
	/// </summary>
	/// <param name="TagName">작동할 어빌리티의 Tag</param>
	void AbilityActivateWithTag(FString Tag);

	/// <summary>
	/// 태그가 0보다 작으면 true 아니면 false 반환
	/// </summary>
	/// <param name="Tag"></param>
	/// <returns></returns>
	bool TagCountCheak(FName Tag);

	/// <summary>
	/// 공격 작동
	/// </summary>
	virtual void Attack();

	float GetWeaponBaseDamage() const;

	/// <summary>
	/// 피격 모션 인덱스 계산
	/// </summary>
	virtual void HitMontageIndexCalculate(FVector ImpactPoint);

	virtual void HitVectorCalculate(FVector ImpactPoint);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetHitMontageIndex() const { return HitIndex; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector GetHitPoint() const { return HitPoint; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
