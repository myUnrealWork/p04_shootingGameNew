// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "p04_shootingGameNewHUD.generated.h"

UCLASS()
class Ap04_shootingGameNewHUD : public AHUD
{
	GENERATED_BODY()

public:
	Ap04_shootingGameNewHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

