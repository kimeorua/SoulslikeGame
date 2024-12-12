// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChangeState.h"
#include "../Character/BaseCharacter.h"
#include "EnemyAIController.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTT_ChangeState::UBTT_ChangeState()
{
	NodeName = "Change State";
}

EBTNodeResult::Type UBTT_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IsValid(OwnerComp.GetAIOwner()))
	{
		Cast<AEnemyAIController>(OwnerComp.GetAIOwner())->ChangeAiState(State);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

