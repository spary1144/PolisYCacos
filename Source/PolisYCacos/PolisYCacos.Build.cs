// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PolisYCacos : ModuleRules
{
	public PolisYCacos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core"		     , 
			"CoreUObject"    , 
			"Engine"	     ,
			"InputCore"	     , 
			"EnhancedInput"  , 
			"OnlineSubsystem", 
			"OnlineSubsystemUtils",
			"UMG"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineSubsystem", "Slate", "SlateCore"
		});
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		
	}
}
