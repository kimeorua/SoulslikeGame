// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree; //비헤이비어 트리

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent; //비헤이비어 트리 컴포넌트

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent; //블랙보드 컴포넌트

	class UAISenseConfig_Sight* SightConfig; //시각 인지 컴포넌트

	class AEnemyCharacter* Enemy;

	bool FristEncount = false;

protected:
	void BeginPlay()override;
	virtual void OnPossess(APawn* InPawn) override;     //폰 빙의시 호출 되는 함수

public:
	//-------------------------------------------블랙보드 키에 접근시 사용할 이름들-------------------------------------------//

	static const FName TargetActor;
	static const FName SelfActor;
	static const FName AI_State;
	static const FName ASC;
	static const FName Distance;
	static const FName Random;

	//-------------------------------------------블랙보드 키에 접근시 사용할 이름들-------------------------------------------//

	AEnemyAIController();

	UFUNCTION()
	void OnUpdated(TArray<AActor*> const& updated_actors);
	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);
	UFUNCTION()
	void SetPerceptionSystem();

	UFUNCTION(BlueprintCallable)
	void ChangeAiState(enum EAIState State);

	//블랙보드 컴포넌트 반환
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }
};
