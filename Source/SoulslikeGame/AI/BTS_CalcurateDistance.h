// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_CalcurateDistance.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UBTS_CalcurateDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTS_CalcurateDistance();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
