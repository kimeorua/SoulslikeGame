// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_RandomPattern.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UBTS_RandomPattern : public UBTService
{
	GENERATED_BODY()
	
	UBTS_RandomPattern();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
