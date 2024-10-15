// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Enums.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKEGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// 무기 DataAsset 맵
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | DataAsset", meta = (AllowPrivateAccess = "true"))
	TMap < EWeaponType, class UWeaponDataAsset* > WeaponDatas;

	// 방패 DatAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | DataAsset", meta = (AllowPrivateAccess = "true"))
	class UShieldDataAsset* ShieldData;

	// 현재 방패
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons | Actor", meta = (AllowPrivateAccess = "true"))
	class AShield* CurrentShield;

	// 무기 BP 맵
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | Actor", meta = (AllowPrivateAccess = "true"))
	TMap < EWeaponType, class AWeapon* > Weapons;

	FWeaponInfo RequestWeapon;
	FWeaponInfo CurrentWeapon;
	FWeaponInfo OldWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// 무기 DataAsset 을 기반으로 기본 위치에 부착
	/// </summary>
	void WeaponsSetting();

	/// <summary>
	/// 방패 DataAsset 을 기반으로 방패 부착
	/// </summary>
	void ShieldSetting();

	/// <summary>
	/// 무기 선택시 호출
	/// </summary>
	void WeaponSelect(EWeaponType Type);

	/// <summary>
	/// 요청한 무기DataAsset및 BP 반환
	/// </summary>
	/// <returns>RequestWeapon</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FWeaponInfo GetRequestWeaponInfo() const {return RequestWeapon;}

	/// <summary>
	/// 현재 무기 정보 반환
	/// </summary>
	/// <returns>CurrentWeapon</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FWeaponInfo GetCurrentWeaponInfo() const { return CurrentWeapon; }

	/// <summary>
	/// 현재 방패 액터 반환
	/// </summary>
	/// <returns>CurrentShield</returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE AShield* GetCurrentShield() const { return CurrentShield; }

	/// <summary>
	/// 무기 장착
	/// </summary>
	/// <param name="IsEquip">true 면 작동 false면 장착 해제</param>
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(bool IsEquip);

	/// <summary>
	/// 무기 장착 해제 -> 이미 무기가 있을경우 작동 함
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();

	void WeaponAttackStart();
};
