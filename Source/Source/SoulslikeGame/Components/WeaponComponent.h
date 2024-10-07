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

	// 현재 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons | Actor", meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;

	// 현재 무기 DataAsset
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons | DataAsset", meta = (AllowPrivateAccess = "true"))
	class UWeaponDataAsset* CurrentWeaponDataAsset;

	// 방패 DatAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | DataAsset", meta = (AllowPrivateAccess = "true"))
	class UShieldDataAsset* ShieldData;

	// 현재 방패
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons | Actor", meta = (AllowPrivateAccess = "true"))
	class AShield* CurrentAShield;

	// 컴포넌트 소유한 객체
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	class ABaseCharacter* Owner;

	// 무기 BP 맵
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons | Actor", meta = (AllowPrivateAccess = "true"))
	TMap < EWeaponType, class AWeapon* > Weapons;

	// 이전에 사용한 무기 , 무기 변경 도중 취소 되었을경울 되돌리기 위해 저장
	class AWeapon* OldWeapon;

	//이전에 사용한 무기DatAsset, 무기 변경 도중 취소 되었을경울 되돌리기 위해 저장
	class UWeaponDataAsset* OldWeaponDataAsset;


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
	/// 무기 장착 도중 취소 되었을 경운, EX: 장착 모션 나오는 도중, 피격
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void CancelWeaponSelect();

	/// <summary>
	/// 현재 무기 BP 및 무기 DataAsset반환
	/// </summary>
	/// <returns>Weapon, WeaponDataAsset</returns>
	UFUNCTION(BlueprintCallable)
	FCurrentWeaponInfo GetCurrentWeaponInfo();
};
