// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameplayTagContainer.h"
#include "../Character/BaseCharacter.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/PlayerCharacter.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense.h"


//접근할 이름에 블랙보드 키값 할당
const FName AEnemyAIController::TargetActor(TEXT("TargetActor"));
const FName AEnemyAIController::SelfActor(TEXT("SelfActor"));
const FName AEnemyAIController::AI_State(TEXT("AI_State"));
const FName AEnemyAIController::ASC(TEXT("ASC"));
const FName AEnemyAIController::Distance(TEXT("Distance"));
const FName AEnemyAIController::Random(TEXT("Random"));

AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	Enemy = nullptr;

	SetPerceptionSystem();

	SetGenericTeamId(FGenericTeamId(1));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BehaviorTree))
	{
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

//빙의시 호출
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard) && IsValid(BehaviorTree))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset); //블랙보드 키값 초기화 실시
		if (Enemy == nullptr)
		{
			Enemy = Cast<AEnemyCharacter>(GetPawn());
			GetBlackboardComponent()->SetValueAsObject(SelfActor, Enemy);
			if (IsValid(Enemy->GetAbilitySystemComponent()))
			{
				GetBlackboardComponent()->SetValueAsObject(ASC, Enemy->GetAbilitySystemComponent());
			}
			else
			{
				GetBlackboardComponent()->SetValueAsObject(ASC, nullptr);
			}
		}
	}
}

void AEnemyAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{

}

void AEnemyAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if (ABaseCharacter* const Target = Cast<ABaseCharacter>(actor))
	{
		if (GetBlackboardComponent()->GetValueAsObject(TargetActor) == nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject(TargetActor, Target);
			
			if (FristEncount == false)
			{
				FristEncount = true;
				ChangeAiState(EAIState::Intro);
			}

			SetFocus(Target);

			Enemy->GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")));
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(TargetActor, nullptr);
			ClearFocus(EAIFocusPriority::Gameplay);

			Enemy->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.UseLockOn")));
		}
	}
}

void AEnemyAIController::SetPerceptionSystem()
{
	//PerceptionComponent할당 및 주요 감지 설정
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	//감지할 객체 정보(적, 중립, 아군)
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;

	//주요 감지 능력 설정
	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());

	//함수 바인딩
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnUpdated);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
}

void AEnemyAIController::ChangeAiState(EAIState State)
{
	if (IsValid(Enemy))
	{
		GetBlackboardComponent()->SetValueAsEnum(AI_State, uint16(State));
	}
}
