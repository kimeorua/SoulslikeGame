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
	// 락온 범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = "true"))
	bool IsLockOn;

	// 바라볼 캐릭터
	class ABaseCharacter* LockOnActor;

	//컴포넌트 소유 한 플레이어 캐릭터
	class APlayerCharacter* Owner;

	// 락온 작동 및 해제용 타이머 핸들
	FTimerHandle LockOnHandle;

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

	/// <summary>
	/// 락온할 객체 탐색
	/// </summary>
	/// <returns></returns>
	ABaseCharacter* TraceForTarget();

	/// <summary>
	///  장애물 판단
	/// </summary>
	/// <returns></returns>
	bool CheackTarget(ABaseCharacter* Target);

	/// <summary>
	/// 락온 작동
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void TriggerTargetLockOn();

	/// <summary>
	/// 타이머를 통해 LockOnActor 바라봄
	/// </summary>
	void TargetLockOn();

	/// <summary>
	/// 락온 중지
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void StopTargetLockOn();

	/// <summary>
	/// 카메라Rotator 계산 및 반환
	/// </summary>
	/// <returns>FRotator 카메라 회전 Rotator</returns>
	FRotator GetLockOnCameraRotation();

	/// <summary>
	/// IsLockOn 반환
	/// </summary>
	/// <returns>IsLockOn</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLockOn() const { return IsLockOn; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
