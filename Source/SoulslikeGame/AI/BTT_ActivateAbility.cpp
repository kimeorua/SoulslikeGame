// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ActivateAbility.h"
#include "../Character/BaseCharacter.h"
#include "EnemyAIController.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTT_ActivateAbility::UBTT_ActivateAbility()
{
	NodeName = "Activte Ability";
}

EBTNodeResult::Type UBTT_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseCharacter* Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (IsValid(Character) && IsValid(Character->GetAbilitySystemComponent()))
	{
		Character->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
