// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SoulslikeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API USoulslikeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	// 캐릭터 무브먼트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components",  meta = (AllowPrivateAccess = "true"))
	class UCharacterMovementComponent* MovementComponent;

	// 캐릭터 GAS 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USoluslikeAbilitySystemComponent* GASComponent;

	// 캐릭터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class ABaseCharacter* Character;;

	// 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Speed;

	// 방향
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	float Direction;

	// 가속 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	bool IsAccelerating;

	// 공중 여부
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	bool IsAir;

public:
	USoulslikeAnimInstance(); // 생성자
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //애니메이션 업데이트 함수

private:
	void SettingVlaue();
};
