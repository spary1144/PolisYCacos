// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"


/**
 * This delegates are in charge of broadcasting when 
 * - Joinning
 * - Creating
 * - Finding
 * - Destroying
 * - ...
 * 
 * This way there is no dependencies of the Menus from the multiplayer subsystem. They are custom created, not from the engine
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindingSessionComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroyingSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

/**
 * @class UMultiplayerSubsystem
 * This class lives inside the GameInstance and can be retrieved by using:
 * 
 * 
 * GameInstance->GetSubsystem<UMultiplayerSubsystem>()
 * 
 * This will manage all lobbies and Steam connections. 
 */
UCLASS()
class MULTIPLAYER_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSubsystem();
	
	/**
	 * This delegates are the ones who broadcast to our menu. Custom made on top of this class
	 */
	FMultiplayerOnCreateSessionComplete		MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindingSessionComplete	MultiplayerOnFindSessionsComplete;
	FMultiplayerOnJoinSessionComplete		MultiplayerOnJoinSessionComplete;
	FMultiplayerOnDestroyingSessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete		MultiplayerOnStartSessionComplete;
		
	void CreateSession(const int32 NumPublicConnections, const FString& SessionName);
	void FindSessions(const int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SearchResult);
	void StartSession();
	void DestroySession();
	
private:
	// Ptr to the Session Interface
	IOnlineSessionPtr SessionInterface;
	
	// Settings for setting up the session
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	
	// Settings for the search of lobbies we are making
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
	/**
	 * Online Interface Delegates and their Callbacks related to:
	 * - Creating Sessions
	 * - Finding Sessions
	 * - Joining Sessions
	 * - Destroying Sessions
	 * - Starting Sessions
	 */
	FOnCreateSessionCompleteDelegate  CreateSessionCompleteDelegate;
	FDelegateHandle					  CreateSessionCompleteDelegateHandle; 
	
	FOnFindSessionsCompleteDelegate   FindSessionsCompleteDelegate;
	FDelegateHandle					  FindSessionsCompleteDelegateHandle;
	
	FOnJoinSessionCompleteDelegate	  JoinSessionCompleteDelegate;
	FDelegateHandle					  JoinSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle					  DestroySessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate	  StartSessionCompleteDelegate;
	FDelegateHandle					  StartSessionCompleteDelegateHandle;
	
	void OnCreatedSession(FName SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccess);
	void OnJoinSessionComplete(FName JoinedSession, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);
	void OnStartSessionComplete(FName SessionName, bool bSuccess);
};


