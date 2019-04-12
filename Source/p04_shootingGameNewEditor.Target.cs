// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class p04_shootingGameNewEditorTarget : TargetRules
{
	public p04_shootingGameNewEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("p04_shootingGameNew");
	}
}
