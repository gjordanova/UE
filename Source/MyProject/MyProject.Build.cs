// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Networking", "Sockets" });
        PublicIncludePaths.Add("D:\\01_Cuca\\01.Proekti\\Task\\boost_1_70_0");
        PublicIncludePaths.Add("D:\\01_Cuca\\01.Proekti\\DriveSim\\include");
        PublicAdditionalLibraries.Add("D:\\01_Cuca\\01.Proekti\\DriveSim\\lib\\DriveSIm-Networking.lib");
        PublicAdditionalLibraries.Add("D:\\01_Cuca\\01.Proekti\\DriveSim\\lib\\DriveSIm-Protocol.lib");

        bEnableUndefinedIdentifierWarnings = false;

        PublicDefinitions.Add("_CRT_HAS_CXX17=0");
        bUseRTTI = true;
    }
}
