// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Journey_Of_Healer : ModuleRules
{
	public Journey_Of_Healer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "UMG" });
	}
}
