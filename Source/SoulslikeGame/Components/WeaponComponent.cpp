// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Character/BaseCharacter.h"
#include "../DataAsset/WeaponDataAsset.h"
#include "../DataAsset/ShieldDataAsset.h"
#include "../Weapons/Weapon.h"
#include "../Weapons/Shield.h"
#include "../Character/BaseCharacter.h"
#include "../Character/PlayerCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"

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
		if (CurrentWeapon.Weapon != nullptr && CurrentWeapon.DataAsset != nullptr)
		{
			Owner->AbilityActivateWithTag("Action.Attack");
		}
		else
		{
			return;
		}
	}
}

void UWeaponComponent::ExecutiomStart()
{
	if (IsValid(CurrentWeapon.Weapon) && IsValid(CurrentWeapon.DataAsset))
	{
		if (ABaseCharacter* Owner = Cast<ABaseCharacter>(GetOwner()))
		{
			Owner->AbilityActivateWithTag("Action.Execution");
		}
	}
}

float UWeaponComponent::GetBaseDamage() const
{
	return IsValid(CurrentWeapon.DataAsset) ? CurrentWeapon.DataAsset->GetBaseDamage() : 0.0f;
}

void UWeaponComponent::WeaponColliison(EAttackType Type)
{
	if (IsValid(CurrentWeapon.Weapon) && IsValid(CurrentWeapon.DataAsset))
	{
		TTuple<bool, ABaseCharacter*, FVector, FVector> TraceData = CurrentWeapon.Weapon->TraceOn(CurrentWeapon.DataAsset->GetCollisionData());

		bool Succes = TraceData.Get<0>();
		ABaseCharacter* HitActor = TraceData.Get<1>();
		FVector Location = TraceData.Get<2>();
		FVector ImpactPoint = TraceData.Get<3>();

		if (Succes && IsValid(HitActor))
		{
			HitActor->ChangeCollision(true);

			switch (Type)
			{
			case EAttackType::None:
				HitActor->HitMontageIndexCalculate(ImpactPoint);
				HitActor->HitVectorCalculate(ImpactPoint);
				SendEvent(HitActor, "Event.Hit.Normal");
				break;
			case EAttackType::Normal:
				if (HitActor->GetWeaponComponent()->AttackGuardCheck(Location))
				{
					if (!(HitActor->TagCountCheak("State.ParryAble.Guard")))
					{
						SendEvent(HitActor, "Event.Hit.GuardParry");
					}
					else
					{
						SendEvent(HitActor, "Event.Hit.Guard");
					}
				}
				else
				{
					if (IsValid(HitActor->GetWeaponComponent()->CurrentShield))
					{
						HitActor->GetWeaponComponent()->CurrentShield->ShieldSizeChange(false);
					}
					HitActor->HitMontageIndexCalculate(ImpactPoint);
					HitActor->HitVectorCalculate(ImpactPoint);
					SendEvent(HitActor, "Event.Hit.Normal");
				}
				break;
			case EAttackType::GuardParryOnly:
				if (HitActor->GetWeaponComponent()->AttackGuardCheck(Location))
				{
					if (!(HitActor->TagCountCheak("State.ParryAble.Guard")))
					{
						SendEvent(HitActor, "Event.Hit.GuardParry");
					}
					else
					{
						if (IsValid(HitActor->GetWeaponComponent()->CurrentShield))
						{
							HitActor->GetWeaponComponent()->CurrentShield->ShieldSizeChange(false);
						}
						HitActor->HitMontageIndexCalculate(ImpactPoint);
						HitActor->HitVectorCalculate(ImpactPoint);
						SendEvent(HitActor, "Event.Hit.Normal");
					}
				}
				else
				{
					if (IsValid(HitActor->GetWeaponComponent()->CurrentShield))
					{
						HitActor->GetWeaponComponent()->CurrentShield->ShieldSizeChange(false);
					}
					HitActor->HitMontageIndexCalculate(ImpactPoint);
					HitActor->HitVectorCalculate(ImpactPoint);

					SendEvent(HitActor, "Event.Hit.Normal");
				}

				break;
			case EAttackType::CounterParryOnly:
				if (!(HitActor->TagCountCheak("State.ParryAble.Counter")))
				{
					if (AttackCounterCheck(HitActor))
					{
						SendEvent(HitActor, "Event.Hit.CounterParry");
					}
					else
					{
						HitActor->HitMontageIndexCalculate(ImpactPoint);
						HitActor->HitVectorCalculate(ImpactPoint);
						SendEvent(HitActor, "Event.Hit.Normal");
					}
				}
				else
				{
					HitActor->HitMontageIndexCalculate(ImpactPoint);
					HitActor->HitVectorCalculate(ImpactPoint);
					SendEvent(HitActor, "Event.Hit.Normal");
				}
				break;

			case EAttackType::Max:
				break;
			default:
				break;
			}
		}
	}
}

bool UWeaponComponent::AttackGuardCheck(FVector Loc)
{
	ABaseCharacter* Owner = CastChecked<ABaseCharacter>(GetOwner());
	if (IsValid(CurrentShield) && !Owner->TagCountCheak("Action.Shield"))
	{
		FVector Location = Loc - GetOwner()->GetActorLocation();
		
		float Drection = UKismetAnimationLibrary::CalculateDirection(Location, GetOwner()->GetActorRotation());

		if (FMath::Abs(Drection) <= 45.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool UWeaponComponent::AttackCounterCheck(ABaseCharacter* Target)
{
	FRotator TargetRot = Target->GetActorRotation();
	FRotator OwnerRot = GetOwner()->GetActorRotation();

	float ParryRot = FMath::Abs(TargetRot.Yaw - OwnerRot.Yaw);

	if (ParryRot >= 130.f && ParryRot <= 230.f)
	{
		Target->CounterTagAttach();
		return true;
	}

	else
	{
		return false;
	}
}

AActor* UWeaponComponent::ExecutionTraceOn()
{
	// 충돌 결과
	FHitResult HitResult;
	bool Succes = false;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetOwner()->GetActorForwardVector() * 80.0f;

	//ABaseCharacter* HitChar;

	// 충돌 검사할 오브젝트 타입
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));

	// 무시할 객체
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Cast<AActor>(GetOwner()));

	Succes = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (Succes)
	{
		//HitChar = Cast<ABaseCharacter>(HitResult.GetActor());
		FVector ExceutionLocation = HitResult.ImpactPoint - (GetOwner()->GetActorForwardVector() * 80.0f);

		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(HitResult.GetActor()->GetActorLocation(), GetOwner()->GetActorLocation());

		GetOwner()->SetActorLocation(ExceutionLocation);
		//HitChar->SetActorRotation(Rot);
		return HitResult.GetActor();
	}
	else
	{
		return nullptr;
	}
}

void UWeaponComponent::VisibleOff()
{
	for (auto T : Weapons)
	{
		AWeapon* Weapon = T.Value;
		Weapon->GetMesh()->SetVisibility(false);
	}

	if (CurrentShield)
	{
		CurrentShield->GetMesh()->SetVisibility(false);
	}
}

void UWeaponComponent::SendEvent(ABaseCharacter* Target, FString Tag)
{
	FGameplayTag EventTag;

	EventTag = FGameplayTag::RequestGameplayTag(FName(Tag));

	FGameplayEventData EventData;
	EventData.Instigator = GetOwner();
	EventData.Target = Target;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), EventTag, EventData);
}


