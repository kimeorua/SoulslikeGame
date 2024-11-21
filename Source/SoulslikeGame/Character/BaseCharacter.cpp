// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "SoulslikeGame/GAS/SoluslikeAbilitySystemComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoulslikeGame/GAS/SoulslikeAttributeSetBase.h"
#include "Components/CapsuleComponent.h"
#include "../Components/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseCharacter::Initalize()
{
	if (!IsValid(SoulslikeGASCompoent) || GetLocalRole() != ROLE_Authority || SoulslikeGASCompoent->StartupEffectApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = SoulslikeGASCompoent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> Effect : InitEffects)
	{
		FGameplayEffectSpecHandle NewHandle = SoulslikeGASCompoent->MakeOutgoingSpec(Effect, 1, EffectContext);

		if (NewHandle.IsValid())
		{
			SoulslikeGASCompoent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), SoulslikeGASCompoent);
		}
	}
	SoulslikeGASCompoent->StartupEffectApplied = true;
}

void ABaseCharacter::initalizeAbilities()
{
	GiveAbilityMulity(DefaultAbility);
}

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SoulslikeGASCompoent = CreateDefaultSubobject<USoluslikeAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	SoulslikeGASCompoent->SetIsReplicated(true);
	//능력치 변경시 이벤트 호출
	SoulslikeGASCompoent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	CombetColliison = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CombetCollision"));
	CombetColliison->SetupAttachment(RootComponent);
	CombetColliison->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	CombetColliison->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

	//기본 Gameplay Effect, GameplayAbility 적용
	Initalize();
	initalizeAbilities();
}

void ABaseCharacter::GiveAbilitySingle(TSubclassOf<class UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (HasAuthority()) { SoulslikeGASCompoent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel)); }
}

void ABaseCharacter::GiveAbilityMulity(TArray<TSubclassOf<class UGameplayAbility>> AddedAbilities)
{
	for (TSubclassOf<class UGameplayAbility> Ability : AddedAbilities)
	{
		GiveAbilitySingle(Ability, 1);
	}
}

void ABaseCharacter::Equip()
{
}

void ABaseCharacter::Unequip(bool PlayAnim)
{
}

void ABaseCharacter::HitMontageIndexCalculate(FVector ImpactPoint)
{
	FVector Velocity = ImpactPoint - GetActorLocation();
	float Yaw = GetActorRotation().Yaw;
	FRotator Rot;
	Rot.Yaw = Yaw;
	float Diretion = UKismetAnimationLibrary::CalculateDirection(Velocity, Rot);

	if (HitMontage.Num() > 1)
	{
		int MontageAngle = 360 / HitMontage.Num();

		float Base = (UKismetMathLibrary::FTrunc(Diretion + 360)) % 360;

		HitIndex = UKismetMathLibrary::FTrunc(Base / MontageAngle);
	}
	else
	{
		HitIndex = 0;
	}
}

void ABaseCharacter::HitVectorCalculate(FVector ImpactPoint)
{
	HitPoint = ImpactPoint;
}

UAnimMontage* ABaseCharacter::GetGuardBreakMontage() const
{
	return IsValid(GuardBreakMontage) ? GuardBreakMontage : nullptr;
}

UAnimMontage* ABaseCharacter::GetGuardMontage() const
{
	return IsValid(GuardBreakMontage) ? GuardMontage : nullptr;
}

UAnimMontage* ABaseCharacter::GetGuardParryMontage() const
{
	return IsValid(GuardBreakMontage) ? GuardParryMontage : nullptr;
}

void ABaseCharacter::GuardBreak()
{
	AbilityActivateWithTag("Action.GuardBreak");
}

void ABaseCharacter::CounterParry()
{
	AbilityActivateWithTag("Action.CounterParry");
}

void ABaseCharacter::CounterTagDeattach()
{
	if (IsValid(GetAbilitySystemComponent()))
	{
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.ExecutionAble")));
	}
}

void ABaseCharacter::ChangeCollision()
{
	CombetColliison->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	FTimerHandle JumpTimerHandle;
	GetWorldTimerManager().SetTimer(JumpTimerHandle, FTimerDelegate::CreateLambda([this]() {CombetColliison->SetCollisionObjectType((ECollisionChannel::ECC_GameTraceChannel2)); }), AvoidTime, false);
}

void ABaseCharacter::CounterTagAttach()
{
	if (IsValid(GetAbilitySystemComponent()))
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.ExecutionAble")));

		FTimerHandle TagRemoveHandle;

		GetWorldTimerManager().SetTimer(TagRemoveHandle, this, &ABaseCharacter::CounterTagDeattach, 3.0f, false);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(SoulslikeGASCompoent))
	{
		AttributeSetVar = SoulslikeGASCompoent->GetSet<USoulslikeAttributeSetBase>();

		//기본 Gameplay Effect, GameplayAbility 적용
		Initalize();
		initalizeAbilities();
	}

	if (IsValid(GetWeaponComponent()))
	{
		GetWeaponComponent()->WeaponsSetting();
		GetWeaponComponent()->ShieldSetting();
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

void ABaseCharacter::AbilityActivateWithTag(FString Tag)
{
	//매개변수 Tag를 받아서 TagContainer를 작성하고, 해당 Tag를 가진 Ability 작동
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(Tag)));
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
}

bool ABaseCharacter::TagCountCheak(FName Tag)
{
	return GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag(Tag)) <= 0;
}

void ABaseCharacter::Attack()
{
	if (TagCountCheak("State.ExecutionAble"))
	{
		GetWeaponComponent()->WeaponAttackStart();
	}
	else
	{
		GetWeaponComponent()->ExecutiomStart();
	}
}

float ABaseCharacter::GetWeaponBaseDamage() const
{
	if (IsValid(GetWeaponComponent()))
	{
		return GetWeaponComponent()->GetBaseDamage();
	}
	else
	{
		return 0.0f;
	}
}
