// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Character/BaseCharacter.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../DataAsset/ShieldDataAsset.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Shield.h"
#include "../Character/BaseCharacter.h"

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

	if (Cast<ABaseCharacter>(GetOwner()))
	{
		Owner = Cast<ABaseCharacter>(GetOwner());

		WeaponsSetting();
		ShieldSetting();
	}
	
}

void UWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::WeaponsSetting()
{
	for (auto item : WeaponDatas)
	{
		if (IsValid(WeaponDatas.FindRef(item.Key)))
		{
			AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(item.Value->GetWeaponClass());
			Weapon->OwnerSet(Owner);
			Weapon->Attach(item.Value->GetUnequipSokcet());

			Weapons.Add(item.Key, Weapon);
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

void UWeaponComponent::WeaponSelect(EWeaponType Type)
{
	if (CurrentWeaponDataAsset == nullptr)
	{
		CurrentWeaponDataAsset = WeaponDatas.FindRef(Type);
		CurrentWeapon = Weapons.FindRef(Type);
	}
	else
	{
		if (CurrentWeaponDataAsset->GetWeaponType() == Type)
		{
			CurrentWeaponDataAsset = nullptr;
			CurrentWeapon = nullptr;
		}
		else
		{
			OldWeaponDataAsset = CurrentWeaponDataAsset;
			OldWeapon = CurrentWeapon;

			CurrentWeaponDataAsset = WeaponDatas.FindRef(Type);
			CurrentWeapon = Weapons.FindRef(Type);
		}
	}
}

void UWeaponComponent::CancelWeaponSelect()
{
	if (CurrentWeaponDataAsset != OldWeaponDataAsset)
	{
		CurrentWeaponDataAsset = OldWeaponDataAsset;
	}
	if (CurrentWeapon != OldWeapon)
	{
		CurrentWeapon = OldWeapon;
	}
}

FCurrentWeaponInfo UWeaponComponent::GetCurrentWeaponInfo()
{
	FCurrentWeaponInfo Info;
	if (CurrentWeapon != nullptr && CurrentWeaponDataAsset != nullptr)
	{
		Info.EquipWeapon = CurrentWeapon;
		Info.EquipWeaponDataAsset = CurrentWeaponDataAsset;
	}
	return Info;
}

