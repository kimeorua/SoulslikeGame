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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TMap < EWeaponType, class UWeaponDataAsset* > Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | Test", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> TestWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons | Test", meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	class ABaseCharacter* Owner;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
