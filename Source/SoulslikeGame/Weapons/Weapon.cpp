// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Attach(FName Socket)
{
	Super::Attach(Socket);
}
