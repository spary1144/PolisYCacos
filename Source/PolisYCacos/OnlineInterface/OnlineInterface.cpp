#include "OnlineInterface.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

UOnlineInterface* UOnlineInterface::Instance = nullptr;

UOnlineInterface::UOnlineInterface()
{
	OnlineSubsystemPtr  = nullptr;
	SessionInterfacePtr = nullptr;
}

void UOnlineInterface::Initialize()
{
	OnlineSubsystemPtr = IOnlineSubsystem::Get();
	
	if (!OnlineSubsystemPtr)
	{
		return;
	}
	SessionInterfacePtr = OnlineSubsystemPtr->GetSessionInterface();
	
	if (!SessionInterfacePtr.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionManager: no se pudo obtener la interfaz de sesión."));
	}
	
	CreateSessionCompleteDelegateHandle = SessionInterfacePtr->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineInterface::OnCreateSessionComplete));
	FindSessionCompleteDelegateHandle	= SessionInterfacePtr->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &UOnlineInterface::OnFindSessionComplete));
	JoinSessionCompleteDelegateHandle	= SessionInterfacePtr->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UOnlineInterface::OnJoinSessionComplete));
	CreateSessionCompleteDelegateHandle = SessionInterfacePtr->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineInterface::OnCreateSessionComplete));
	
}

void UOnlineInterface::CreateGameSession(const int32 MaxPlayers, const FString& SessionName, const bool OnlyFriendsCanJoin) const
{
	FOnlineSessionSettings Settings;
	Settings.bIsLANMatch			= false;
	Settings.bShouldAdvertise		= true;
	Settings.NumPublicConnections	= MaxPlayers;
	Settings.bUsesPresence			= true;
	Settings.bAllowJoinInProgress	= true;
	Settings.bAllowInvites			= false;
	Settings.bAllowJoinViaPresence	= true;
	Settings.bAllowJoinViaPresenceFriendsOnly = OnlyFriendsCanJoin;
	
	if (SessionInterfacePtr->CreateSession(0, *SessionName, Settings))
	{
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS CREATING THE LOBBY"));
	}
}

void UOnlineInterface::FindGameSessions()
{
	if (!SessionInterfacePtr.IsValid())
	{
		return;
	}
	SessionSearch					= MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100;
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	SessionInterfacePtr->FindSessions(0, SessionSearch.ToSharedRef());
}

void UOnlineInterface::OnFindSessionComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		return;
	}
	if (SessionSearch.IsValid())
	{
		SessionSearchResult = SessionSearch->SearchResults;
	}
	OnFindSessionsCompleteDelegate.Broadcast();
}

void UOnlineInterface::JoinGameSession(const int32 Index)
{
	if (!SessionInterfacePtr.IsValid() || !SessionSearchResult.IsValidIndex(Index))
	{
		return;
	}
	SessionInterfacePtr->JoinSession(0, NAME_GameSession, SessionSearchResult[Index]);
}

void UOnlineInterface::JoinGameSession(const FString& SessionID)
{
	if (!SessionInterfacePtr.IsValid())
	{
		return;
	}
	
	FOnlineSessionSearchResult SearchResult;
	
}

void UOnlineInterface::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	OnJoinSessionCompleteDelegate.Broadcast(Result == EOnJoinSessionCompleteResult::Success);
}

UOnlineInterface* UOnlineInterface::Get() 
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UOnlineInterface>();
		Instance->AddToRoot();
		Instance->Initialize();
	}
	return Instance;
}

void UOnlineInterface::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	OnCreateSessionCompleteDelegate.Broadcast(bSuccess);
	
	if (!bSuccess)
	{
		return;
	}
	
	const FNamedOnlineSession* Session = SessionInterfacePtr->GetNamedSession(NAME_GameSession);
	if (!Session)
	{
		return;
	}
	
	Session->SessionSettings.Get(FName("SteamLobbyId"), LobbyID);
	if (LobbyID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("LobbyID is empty"));
	}
}
