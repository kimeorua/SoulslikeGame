// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulslikeAttributeSetBase.h"
#include "Net/UnrealNetwork.h"

void USoulslikeAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Health, OldHealth);
}

void USoulslikeAttributeSetBase::OnRep_Will(const FGameplayAttributeData& OldWill)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Will, OldWill);
}

void USoulslikeAttributeSetBase::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Strength, OldStrength);
}

void USoulslikeAttributeSetBase::OnRep_Talent(const FGameplayAttributeData& OldTalent)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Talent, OldTalent);
}

void USoulslikeAttributeSetBase::OnRep_Concentration(const FGameplayAttributeData& OldConcentration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Concentration, OldConcentration);
}

void USoulslikeAttributeSetBase::OnRep_HP(const FGameplayAttributeData& OldHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, HP, OldHP);
}

void USoulslikeAttributeSetBase::OnRep_SP(const FGameplayAttributeData& OldSP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, SP, OldSP);
}

void USoulslikeAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, Mana, OldMana);
}

void USoulslikeAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Will, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Talent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Concentration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, SP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
}


void USoulslikeAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange"));
}

void USoulslikeAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute"));
}
