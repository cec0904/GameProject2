// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject2 : ModuleRules
{
	public GameProject2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule" });
	}
}
