#include "MultiplayerSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Engine/Engine.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerSubsystem::UMultiplayerSubsystem()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	
	if (!OnlineSubsystem)
	{
		if (GEngine)
		{
			UE_LOG(LogTemp, Warning, TEXT("No online subsystem found. UMultiplayerSubsystem not initialized"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No online subsystem found. UMultiplayerSubsystem not initialized"));
		}
		return;
	}
	
	SessionInterface = OnlineSubsystem->GetSessionInterface();
	
	CreateSessionCompleteDelegate  = FOnCreateSessionCompleteDelegate::CreateUObject(this , &UMultiplayerSubsystem::OnCreatedSession);
	FindSessionsCompleteDelegate   = FOnFindSessionsCompleteDelegate::CreateUObject(this  , &UMultiplayerSubsystem::OnFindSessionsComplete);
	JoinSessionCompleteDelegate    = FOnJoinSessionCompleteDelegate::CreateUObject(this   , &UMultiplayerSubsystem::OnJoinSessionComplete);
	DestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UMultiplayerSubsystem::OnDestroySessionComplete);
	StartSessionCompleteDelegate   = FOnStartSessionCompleteDelegate::CreateUObject(this  , &UMultiplayerSubsystem::OnStartSessionComplete);

}

bool UMultiplayerSubsystem::IsValidSessionInterface()
{
	if (!SessionInterface)
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem)
		{
			SessionInterface = OnlineSubsystem->GetSessionInterface();
		}
	}
	return SessionInterface.IsValid();
}

void UMultiplayerSubsystem::CreateSession(const int32 NumPublicConnections, const FString& SessionName)
{
	if (!IsValidSessionInterface())
		return;
	
	if (SessionInterface->GetNamedSession(NAME_GameSession))
	{
		bCreateSessionOnDestroy  = true;
		LastNumPublicConnections = NumPublicConnections;
		LastMatchType			 = SessionName;
		DestroySession();
	}
	
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	LastSessionSettings->bIsLANMatch			= IOnlineSubsystem::Get()->GetSubsystemName().IsEqual("NULL");
	LastSessionSettings->bShouldAdvertise		= true;
	LastSessionSettings->bAllowJoinInProgress	= true;
	LastSessionSettings->bAllowJoinViaPresence	= true;
	// Las dos siguientes lineas son necesarias a partir de 5.6
	LastSessionSettings->bUsesPresence			= true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->BuildUniqueId			= 1;
	LastSessionSettings->Set(FName("MatchType"), SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	// Estos mas adelante parametrizables
	LastSessionSettings->bAllowInvites			= false;
	LastSessionSettings->NumPublicConnections	= NumPublicConnections;
		
	if (!GetWorld())
		return;
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();  
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle( CreateSessionCompleteDelegateHandle);
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

void UMultiplayerSubsystem::OnCreatedSession(FName SessionName, bool bSuccess)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	MultiplayerOnCreateSessionComplete.Broadcast(bSuccess);
}

void UMultiplayerSubsystem::FindSessions(const int32 MaxSearchResults)
{
	if (!IsValidSessionInterface())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FindSessions SessionInterface invalid"));
			UE_LOG(LogTemp, Warning, TEXT("FindSessions SessionInterface invalid"));
		}
		return;
	}
	
	FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
	
	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery		= IOnlineSubsystem::Get()->GetSubsystemName().IsEqual("NULL");
	
	LastSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SesionInterface-> FindSessions Failed Finding Sessions"));
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
		MultiplayerOnFindSessionsComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
	}
}

void UMultiplayerSubsystem::OnFindSessionsComplete(bool bSuccess)
{
	if (SessionInterface)
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
	
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UMultiplayerSubsystem::OnFindSessionComplete Reached"));
	
	if (LastSessionSearch->SearchResults.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UMultiplayerSubsystem::OnFindSessionCompleteNo Sessions Found!"));
		MultiplayerOnFindSessionsComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
		return;
	}
			
	MultiplayerOnFindSessionsComplete.Broadcast(LastSessionSearch->SearchResults, bSuccess);
}

void UMultiplayerSubsystem::JoinSession(const FOnlineSessionSearchResult& SearchResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UMultiplayerSubsystem::JoinSession Reached"));
	//if (!SessionInterface.IsValid())
	if (!IsValidSessionInterface())
	{
		MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}
	
	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SearchResult))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		MultiplayerOnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
	}
}

void UMultiplayerSubsystem::OnJoinSessionComplete(FName JoinedSession, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface)
		return;
	
	SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	MultiplayerOnJoinSessionComplete.Broadcast(Result);
}

void UMultiplayerSubsystem::StartSession()
{
	if (!IsValidSessionInterface())
	{
		MultiplayerOnStartSessionComplete.Broadcast(false);
		return;
	}
	StartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegate);
	
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!LocalPlayer)
	{
		MultiplayerOnStartSessionComplete.Broadcast(false);
		return;
	}
	
	if (!SessionInterface->StartSession(NAME_GameSession))
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
		MultiplayerOnStartSessionComplete.Broadcast(false);
	}
}

void UMultiplayerSubsystem::OnStartSessionComplete(FName SessionName, bool bSuccess)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session Started Successfully!")));
	}
	
	MultiplayerOnStartSessionComplete.Broadcast(bSuccess);
}

void UMultiplayerSubsystem::DestroySession()
{
	if (!IsValidSessionInterface())
	{
		MultiplayerOnDestroySessionComplete.Broadcast(false);
		return;
	}
	
	
	DestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);
	if (!SessionInterface->DestroySession(NAME_GameSession))
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		MultiplayerOnDestroySessionComplete.Broadcast(false);
	}
	
}

void UMultiplayerSubsystem::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	}
	if (bSuccess && bCreateSessionOnDestroy)
	{
		bCreateSessionOnDestroy = false;
		CreateSession(LastNumPublicConnections, LastMatchType);
	}
	MultiplayerOnDestroySessionComplete.Broadcast(bSuccess);
}


