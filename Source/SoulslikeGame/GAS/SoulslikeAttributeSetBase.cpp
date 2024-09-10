// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulslikeAttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

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

void USoulslikeAttributeSetBase::OnRep_MaxStat(const FGameplayAttributeData& OldMaxStat)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USoulslikeAttributeSetBase, MaxStat, OldMaxStat);
}

void USoulslikeAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Health, COND_None, REPNOTIFY_Always); //체력
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Will, COND_None, REPNOTIFY_Always); //의지
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Strength, COND_None, REPNOTIFY_Always); //근력
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Talent, COND_None, REPNOTIFY_Always); //재능
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Concentration, COND_None, REPNOTIFY_Always); //집중
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, MaxStat, COND_None, REPNOTIFY_Always); //최대 스탯
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, SP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USoulslikeAttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
}


void USoulslikeAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange %s, %f"), *Attribute.AttributeName, NewValue);
}

void USoulslikeAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute: %s"), *Data.EvaluatedData.Attribute.AttributeName);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxStat()));
	}
	else if (Data.EvaluatedData.Attribute == GetWillAttribute())
	{
		SetWill(FMath::Clamp(GetWill(), 0.0f, GetMaxStat()));
	}
	else if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(), 0.0f, GetMaxStat()));
	}
	else if (Data.EvaluatedData.Attribute == GetTalentAttribute())
	{
		SetTalent(FMath::Clamp(GetTalent(), 0.0f, GetMaxStat()));
	}
	else if (Data.EvaluatedData.Attribute == GetConcentrationAttribute())
	{
		SetConcentration(FMath::Clamp(GetConcentration(), 0.0f, GetMaxStat()));
	}
}
