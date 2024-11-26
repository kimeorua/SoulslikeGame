// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_CalcurateDistance.h"
#include "../Character/BaseCharacter.h"
#include "EnemyAIController.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTS_CalcurateDistance::UBTS_CalcurateDistance()
{
	NodeName = "Calcurate Distance";
}

void UBTS_CalcurateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyAIController* AI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	ABaseCharacter* Self = Cast<ABaseCharacter>(AI->GetBlackboardComponent()->GetValueAsObject(AI->SelfActor));
	ABaseCharacter* Target = Cast<ABaseCharacter>(AI->GetBlackboardComponent()->GetValueAsObject(AI->TargetActor));

	if (IsValid(Self) && IsValid(Target))
	{
		double Distance = UKismetMathLibrary::Vector_Distance2D(Self->GetActorLocation(), Target->GetActorLocation());

		AI->GetBlackboardComponent()->SetValueAsFloat(AI->Distance, Distance);
	}
}
