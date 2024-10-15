// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "Components/StaticMeshComponent.h"
#include "../Character/BaseCharacter.h"

AShield::AShield()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ActivateSize = FVector(0.65f, 0.75f, 0.55f);
	DeactivateSize = FVector(0.2f, 0.2f, 0.2f);
}

void AShield::BeginPlay()
{
	Super::BeginPlay();
}

void AShield::Attach(FName Socket)
{
	this->AttachToComponent(GetOwner()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
}

void AShield::ShieldSizeChange(bool isActivate)
{
	if (isActivate)
	{
		Mesh->SetWorldScale3D(ActivateSize);
	}
	else
	{
		Mesh->SetWorldScale3D(DeactivateSize);
	}
}
