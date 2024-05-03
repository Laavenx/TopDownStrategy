// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownGameMode.h"

#include "TopDownGameState.h"
#include "TopDownStrategy/Character/Player/TopDownPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATopDownGameMode::ATopDownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Player/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Player/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ATopDownGameState> GameStateBPClass(TEXT("/Game/TopDown/GameObjects/BP_TopDownGameState"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		GameStateClass = GameStateBPClass.Class;
	}
}