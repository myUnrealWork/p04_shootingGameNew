// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "p04_shootingGameNewGameMode.h"
#include "p04_shootingGameNewHUD.h"
#include "p04_shootingGameNewCharacter.h"
#include "UObject/ConstructorHelpers.h"

Ap04_shootingGameNewGameMode::Ap04_shootingGameNewGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Ap04_shootingGameNewHUD::StaticClass();
}
