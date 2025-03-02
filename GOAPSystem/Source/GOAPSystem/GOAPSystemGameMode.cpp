// Copyright Epic Games, Inc. All Rights Reserved.

#include "GOAPSystemGameMode.h"
#include "GOAPSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGOAPSystemGameMode::AGOAPSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
