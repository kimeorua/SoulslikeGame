// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeChangeAsyncTask.h"

UAttributeChangeAsyncTask* UAttributeChangeAsyncTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemCompoenet, FGameplayAttribute Attribute)
{
	//Static 함수호출시 UAsyncTaskAttributeChanged 클래스 생성뒤 실행
	UAttributeChangeAsyncTask* WaitforAttributeChangedTask = NewObject<UAttributeChangeAsyncTask>();

	//블루프린트에서 넣은 해당 정보 기입
	WaitforAttributeChangedTask->ASC = AbilitySystemCompoenet;
	WaitforAttributeChangedTask->AttributeToListenFor = Attribute;

	//파라미터가 잘못되면
	if (!IsValid(AbilitySystemCompoenet) || !Attribute.IsValid())
	{
		//생성한 오브젝트를 다시 지운다, 언리얼꺼라 알아서 나중에 지워짐
		WaitforAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}
	AbilitySystemCompoenet->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitforAttributeChangedTask, &UAttributeChangeAsyncTask::AttributeChanged);

	return WaitforAttributeChangedTask;

}

UAttributeChangeAsyncTask* UAttributeChangeAsyncTask::ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemCompoenet, TArray<FGameplayAttribute> Attributes)
{
	//Static 함수호출시 UAsyncTaskAttributeChanged 클래스 생성뒤 실행
	UAttributeChangeAsyncTask* WaitforAttributeChangedTask = NewObject<UAttributeChangeAsyncTask>();

	//블루프린트에서 넣은 해당 정보 기입
	WaitforAttributeChangedTask->ASC = AbilitySystemCompoenet;
	WaitforAttributeChangedTask->AttributesToListenFor = Attributes;

	//파라미터가 잘못되면
	if (!IsValid(AbilitySystemCompoenet) || Attributes.Num() < 1)
	{
		//생성한 오브젝트를 다시 지운다, 언리얼꺼라 알아서 나중에 지워짐
		WaitforAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	//여러개 한번에 등록
	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemCompoenet->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitforAttributeChangedTask, &UAttributeChangeAsyncTask::AttributeChanged);
	}

	return WaitforAttributeChangedTask;
}

void UAttributeChangeAsyncTask::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		//여러개
		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	//테스크 삭제
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAttributeChangeAsyncTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	//Health,새로운 HP,이전 HP
	OnAttributgeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
