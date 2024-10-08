// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKEGAME_API AShield : public AProp
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

public:
	AShield();

	virtual void BeginPlay() override;

	virtual void Attach(FName Socket)override;
	
};
