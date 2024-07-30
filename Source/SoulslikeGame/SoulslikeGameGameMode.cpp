// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulslikeGameGameMode.h"
#include "SoulslikeGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoulslikeGameGameMode::ASoulslikeGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
