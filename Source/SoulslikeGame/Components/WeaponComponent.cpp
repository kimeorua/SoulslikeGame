// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Character/BaseCharacter.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../DataAsset/ShieldDataAsset.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Shield.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentWeapon = nullptr;
	Owner = nullptr;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ABaseCharacter>(GetOwner());

	WeaponsSetting();
	ShieldSetting();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::WeaponsSetting()
{
	for (auto item : Weapons )
	{
		if (IsValid(Weapons.FindRef(item.Key)))
		{
			AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(item.Value->GetWeaponClass());
			Weapon->OwnerSet(Owner);
			Weapon->Attach(item.Value->GetUnequipSokcet());
		}
	}
}

void UWeaponComponent::ShieldSetting()
{
	if (IsValid(ShieldData))
	{
		CurrentAShield = GetWorld()->SpawnActor<AShield>(ShieldData->GetShieldClass());
		CurrentAShield->OwnerSet(Owner);
		CurrentAShield->Attach(ShieldData->GetEquipSokcet());
	}
}

