// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API AShield : public AProp
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	//  방어 시 방패 사이즈
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Activate Size", meta = (AllowPrivateAccess = "true"))
	FVector ActivateSize;

	// 방패 기본 사이즈
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Activate Size", meta = (AllowPrivateAccess = "true"))
	FVector DeactivateSize;

public:
	AShield();

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	virtual void BeginPlay() override;

	virtual void Attach(FName Socket)override;

	/// <summary>
	/// 방패 사이즈 변경 함수 -> 애님노티파이에서 실행
	/// </summary>
	/// <param name="isActivate">작동 여부</param>
	UFUNCTION(BlueprintCallable)
	void ShieldSizeChange(bool isActivate);

	bool GuardCheack();
	
};
