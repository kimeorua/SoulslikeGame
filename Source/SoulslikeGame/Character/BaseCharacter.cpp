// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "SoulslikeGame/GAS/SoluslikeAbilitySystemComponent.h"
#include "SoulslikeGame/GAS/SoulslikeAttributeSetBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SoulslikeGASCompoent = CreateDefaultSubobject<USoluslikeAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	SoulslikeGASCompoent->SetIsReplicated(true);
	//능력치 변경시 이벤트 호출
	SoulslikeGASCompoent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (SoulslikeGASCompoent != nullptr)
	{
		SoulslikeGASCompoent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SoulslikeGASCompoent->InitAbilityActorInfo(this, this);

	//initalize
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(SoulslikeGASCompoent))
	{
		AttributeSetVar = SoulslikeGASCompoent->GetSet<USoulslikeAttributeSetBase>();
		//initalize
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

