// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Character/BaseCharacter.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../DataAsset/ShieldDataAsset.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Shield.h"
#include "../Character/BaseCharacter.h"
#include "../Character/PlayerCharacter.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentShield = nullptr;
	ShieldData = nullptr;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
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
	for (TTuple<EWeaponType, class UWeaponDataAsset*> item : WeaponDatas)
	{
		if (IsValid(WeaponDatas.FindRef(item.Key)))
		{
			AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(item.Value->GetWeaponClass());
			Weapon->OwnerSet(Cast<ABaseCharacter>(GetOwner()));
			Weapon->Attach(item.Value->GetUnequipSokcet());

			Weapons.Add(item.Key, Weapon);
		}
	}
}

void UWeaponComponent::ShieldSetting()
{
	if (IsValid(ShieldData))
	{
		CurrentShield = GetWorld()->SpawnActor<AShield>(ShieldData->GetShieldClass());
		CurrentShield->OwnerSet(Cast<ABaseCharacter>(GetOwner()));
		CurrentShield->Attach(ShieldData->GetEquipSokcet());
	}
}

void UWeaponComponent::WeaponSelect(EWeaponType Type)
{
	if (IsValid(Weapons.FindRef(Type)))
	{
		if (CurrentWeapon.Weapon == nullptr || CurrentWeapon.DataAsset == nullptr)
		{
			RequestWeapon.DataAsset = WeaponDatas.FindRef(Type);
			RequestWeapon.Weapon = Weapons.FindRef(Type);
		}
		else
		{
			if (CurrentWeapon.DataAsset->GetWeaponType() == Type)
			{
				RequestWeapon.DataAsset = nullptr;
				RequestWeapon.Weapon = nullptr;
			}
			else
			{
				OldWeapon.DataAsset = CurrentWeapon.DataAsset;
				OldWeapon.Weapon = CurrentWeapon.Weapon;

				RequestWeapon.DataAsset = WeaponDatas.FindRef(Type);
				RequestWeapon.Weapon = Weapons.FindRef(Type);
			}
		}
	}
}

void UWeaponComponent::EquipWeapon(bool IsEquip)
{
	if (IsEquip)
	{
		if (CurrentWeapon.DataAsset == nullptr && CurrentWeapon.Weapon == nullptr)
		{
			CurrentWeapon.DataAsset = RequestWeapon.DataAsset;
			CurrentWeapon.Weapon = RequestWeapon.Weapon;

			CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetEquipSokcet());
		}
		else
		{
			CurrentWeapon.DataAsset = RequestWeapon.DataAsset;
			CurrentWeapon.Weapon = RequestWeapon.Weapon;

			CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetEquipSokcet());
		}
	}
	else
	{
		CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetUnequipSokcet());
		CurrentWeapon.DataAsset = RequestWeapon.DataAsset;
		CurrentWeapon.Weapon = RequestWeapon.Weapon;
	}
}

void UWeaponComponent::UnequipWeapon()
{
	if (CurrentWeapon.DataAsset != nullptr && CurrentWeapon.Weapon != nullptr)
	{
		CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetUnequipSokcet());

		CurrentWeapon.Weapon = nullptr;
		CurrentWeapon.DataAsset = nullptr;
	}
}

void UWeaponComponent::WeaponAttackStart()
{
	if (ABaseCharacter*Owner = Cast<ABaseCharacter>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponComponent::Attack"));
		Owner->AbilityActivateWithTag("Action.Attack");
	}
}
