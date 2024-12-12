// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_RandomPattern.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_RandomPattern::UBTS_RandomPattern()
{
	NodeName = "Random Pattern";
	bNotifyBecomeRelevant = true;
}

void UBTS_RandomPattern::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AEnemyAIController* AI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	int32 Random = FMath::RandRange(0, 100);

	AI->GetBlackboardComponent()->SetValueAsInt(AI->Random, Random);

	UE_LOG(LogTemp, Warning, TEXT("HI"));
}
