#include "OnlineInterface.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
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
	
}

void UOnlineInterface::CreateGameSession(const int32 MaxPlayers, const FString& SessionName, const bool OnlyFriendsCanJoin) const
{
	FOnlineSessionSettings Settings;
	//Settings.bIsLANMatch			= false;
	Settings.bIsLANMatch			= true;
	
	Settings.bShouldAdvertise		= true;
//	Settings.NumPublicConnections	= MaxPlayers;
	
	Settings.NumPublicConnections	= 4;
	//Settings.bUsesPresence			= true;
	Settings.bUsesPresence			= false;
	
	Settings.bAllowJoinInProgress	= true;
	Settings.bAllowInvites			= false;
	//Settings.bAllowJoinViaPresence	= true;
	Settings.bAllowJoinViaPresence	= false;
	
	Settings.bAllowJoinViaPresenceFriendsOnly = OnlyFriendsCanJoin;
	
	//Settings.Set("LOBBY_NAME", SessionName, EOnlineDataAdvertisementType::ViaOnlineService);
	
	// Creo que con esto podemos hacer el nombre del mapa
	//Settings.Set(FName(TEXT("MAP_NAME")), FString(TEXT("MiMapa")), EOnlineDataAdvertisementType::ViaOnlineService);
	
	if (SessionInterfacePtr->CreateSession(0, NAME_GameSession, Settings))
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
	SessionSearch->MaxSearchResults = 50;
	SessionSearch->bIsLanQuery = true;
	
	//SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("Num of games found %i"), SessionSearchResult.Num()));
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
	if (!Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby could not be joined"));
		return;
	}
	
	FString ConnectString; 
	if (!SessionInterfacePtr->GetResolvedConnectString(SessionName, ConnectString))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby could not be joined (ConnectString Missing)"));
		return; 
	}
	
	const UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby could not be joined (World Missing)"));
		return;
	}
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (IsValid(PlayerController))
	{
		PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
	}
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
// hay que suscribirse a eventos de este estilo para gestionar la información porque si no puedo estar obteniendo lenght antes de rellenar el vector

void UOnlineInterface::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	static int32 CreateSessionCompletedCount = 0;
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete #%d (Success=%d)"),  ++CreateSessionCompletedCount, bSuccess);
	OnCreateSessionCompleteDelegate.Broadcast(bSuccess);
	
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby could not be created"));

		return;
	}
	
	const FNamedOnlineSession* Session = SessionInterfacePtr->GetNamedSession(NAME_GameSession);
	if (!Session)
	{
		return;
	}
	
	if (LobbyID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("LobbyID is empty"));
	}
	
	const FString LobbyMapPath = "/Game/Maps/Lobby/L_Lobby?listen";
	
	if (GetWorld())
		GetWorld()->ServerTravel(LobbyMapPath);
}
