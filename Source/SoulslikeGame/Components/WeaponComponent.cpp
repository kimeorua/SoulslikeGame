// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Character/BaseCharacter.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../Weapons/Weapon.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentWeapon = nullptr;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ABaseCharacter>(GetOwner());
	
	if (IsValid(Weapons.FindRef(EWeaponType::Sword)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hi %s"), *Weapons.FindRef(EWeaponType::Sword)->GetWeaponClass()->GetName());
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(Weapons.FindRef(EWeaponType::Sword)->GetWeaponClass());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hi"));
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

