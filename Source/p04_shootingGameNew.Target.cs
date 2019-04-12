// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class p04_shootingGameNewTarget : TargetRules
{
	public p04_shootingGameNewTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("p04_shootingGameNew");
	}
}
