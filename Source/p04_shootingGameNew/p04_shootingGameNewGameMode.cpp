// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "p04_shootingGameNewGameMode.h"
#include "p04_shootingGameNewHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Navmesh/NavMeshBoundsVolume.h"

Ap04_shootingGameNewGameMode::Ap04_shootingGameNewGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behaviour/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Ap04_shootingGameNewHUD::StaticClass();
}
