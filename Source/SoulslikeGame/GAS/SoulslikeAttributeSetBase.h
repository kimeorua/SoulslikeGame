// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SoluslikeAbilitySystemComponent.h"
#include "SoulslikeAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class SOULSLIKEGAME_API USoulslikeAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	//체력 스탯(생명력) 1p HP 2 증가, 기본값 100
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Health)

	//의지 스탯 (스태미나) 1p 3증가, 기본값 50
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Will)
	FGameplayAttributeData Will;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Will)

	//근력 스탯 (공격력) 1p 5증가 30스텟 이상부터 1p 3증가
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Strength)

	//재능 스탯(스킬 데미지/회복량) 1p 당 7 증가 / 1p당 1증가 
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Talent)
	FGameplayAttributeData Talent;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Talent)

	//집중 스탯(치명타 확률 / 치명타 데미지 증가) 확률 1p당 1%증가 / 데미지 1p 2%p 증가 || 기본값 10% / 150%
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Concentration)
	FGameplayAttributeData Concentration;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Concentration)

	//스탯의 최대 값
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxStat)
	FGameplayAttributeData MaxStat;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, MaxStat)

	// 캐릭터의 체력
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, HP)

	// 캐릭터의 스태미나
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_SP)
	FGameplayAttributeData SP;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, SP)

	// 캐릭터의 마나
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, Mana)

	// 최대 체력
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, MaxHP)

	//  최대 스태미나
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxSP)
	FGameplayAttributeData MaxSP;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, MaxSP)

	//  최대 마나
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USoulslikeAttributeSetBase, MaxMana)

public:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_Will(const FGameplayAttributeData& OldWill);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION()
	virtual void OnRep_Talent(const FGameplayAttributeData& OldTalent);

	UFUNCTION()
	virtual void OnRep_Concentration(const FGameplayAttributeData& OldConcentration);

	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	UFUNCTION()
	virtual void OnRep_SP(const FGameplayAttributeData& OldSP);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaxStat(const FGameplayAttributeData& OldMaxStat);

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

	UFUNCTION()
	virtual void OnRep_MaxSP(const FGameplayAttributeData& OlMaxdSP);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
};
