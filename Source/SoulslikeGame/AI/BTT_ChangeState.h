// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Enums.h"
#include "BTT_ChangeState.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API UBTT_ChangeState : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value", meta = (AllowPrivateAccess = "true"))
	EAIState State;

	UBTT_ChangeState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
