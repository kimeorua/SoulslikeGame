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
	class AShield* CurrentAShield;

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
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FWeaponInfo GetRequestWeaponInfo() const {return RequestWeapon;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FWeaponInfo GetCurrentWeaponInfo() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(bool IsEquip);
};
