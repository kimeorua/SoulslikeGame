// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	//카메라가 달릴 스프링 암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//입력 매핑 컨택스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | MappingContext",  meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// 점프 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	// 이동 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// 카메라 시점 회전 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// 달리기 및 회피 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Action", meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAndAvoidAction;

public:
	/// <summary>
	/// 입력 컨택스트 및 입력 설정
	/// </summary>
	/// <param name="PlayerInputComponent">플레이어 입력 컴포넌트</param>
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// <summary>
	///  W, A, S, D 움직임
	/// </summary>
	/// <param name="Value">입력 값</param>
	void Move(const struct FInputActionValue& Value);

	/// <summary>
	/// 카메라 시점 회전
	/// </summary>
	/// <param name="Value">입력 값</param>
	void Look(const struct FInputActionValue& Value);

	/// <summary>
	/// 달리기 시작
	/// </summary>
	void DashStart();

	/// <summary>
	/// 달리기 종료
	/// </summary>
	void DashEnd();

	/// <summary>
	/// 회피 작동
	/// </summary>
	void Avoid();

	/// <summary>
	///  Tag 를 변수로 어빌리티 작동
	/// </summary>
	/// <param name="TagName">작동할 어빌리티의 Tag</param>
	void AbilityActivateWithTag(FString Tag);

protected:
	/// <summary>
	/// 게임 시작 시 호출
	/// </summary>
	virtual void BeginPlay() override;
};
