// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PolisYCacos : ModuleRules
{
	public PolisYCacos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core"		   , "CoreUObject"    , 
			"Engine"	   , "InputCore"	  , 
			"EnhancedInput", "OnlineSubsystem", 
			"OnlineSubsystemUtils"
		});
		
		PrivateDependencyModuleNames.AddRange(new string []{ "OnlineSubsystem" });
		
		DynamicallyLoadedModuleNames.AddRange(new string[] {"OnlineSubsystemSteam"});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
	}
}
