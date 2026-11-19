// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Def_Practica : ModuleRules
{
	public Def_Practica(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
