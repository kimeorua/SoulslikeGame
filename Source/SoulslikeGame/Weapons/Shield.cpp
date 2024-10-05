// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "Components/StaticMeshComponent.h"
#include "../Character/BaseCharacter.h"

AShield::AShield()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AShield::BeginPlay()
{
}

void AShield::Attach(FName Socket)
{
	this->AttachToComponent(GetOwner()->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
}
