// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SoluslikeAbilitySystemComponent.h"
#include "AttributeChangeAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SOULSLIKEGAME_API UAttributeChangeAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributgeChanged; //함수 포인터


	//변경됐을때 블루프린트에서 확인 가능하도록, static이라 아무때나 호출가능
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true))
	static UAttributeChangeAsyncTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemCompoenet, FGameplayAttribute Attribute);

	//속성값 여러개 한번에 획득
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true))
	static UAttributeChangeAsyncTask* ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemCompoenet, TArray<FGameplayAttribute > Attributes);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor; //값 들어있는애 하나
	TArray<FGameplayAttribute > AttributesToListenFor; //값 여러개

	//값 변경 될때 호출
	void AttributeChanged(const FOnAttributeChangeData& Data);
};
