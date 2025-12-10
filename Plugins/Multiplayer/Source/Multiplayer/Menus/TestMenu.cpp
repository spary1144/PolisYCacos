
#include "TestMenu.h"
#include "MultiplayerSubsystem.h"
#include "OnlineSessionSettings.h"

bool UTestMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	if (!IsValid(GetHostSessionButton()) || !IsValid(GetJoinSessionButton()))
	{
		return false;
	}
		
	HostSessionButton->OnClicked.AddDynamic(this, &ThisClass::OnHostSessionButtonClicked);
    JoinSessionButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinSessionButtonClicked);
	
	return true;
}

void UTestMenu::MenuTearDown()
{
	RemoveFromParent();
	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
}

void UTestMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UTestMenu::MenuSetup(const int32 NumberPublicConnections, const FString& TypeOfMatch, const FString& LobbyPath)
{
	NumPublicConnections = NumberPublicConnections;
	MatchType			 = TypeOfMatch;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Lobby Path: %s"), *LobbyPath));
	LobbyMapPath		 = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);
	
	const UWorld* World = GetWorld();
	if (IsValid(World))
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (IsValid(PlayerController))
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			PlayerController->SetShowMouseCursor(true);
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}
	}
	
	const UGameInstance* GameInstance = GetGameInstance();
	if (IsValid(GameInstance))
	{
		MultiplayerSubsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
		
	}
	if (MultiplayerSubsystem)
	{
		// Binding of the callbacks for the session management when ending functions
		MultiplayerSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::CreateSessionCompleteCallback);
		MultiplayerSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::JoinSessionCompleteCallback);
		MultiplayerSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::FindSessionCompleteCallback);
		MultiplayerSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::StartSessionCompleteCallback);
		MultiplayerSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::DestroySessionCompleteCallback);
	}
}

void UTestMenu::OnJoinSessionButtonClicked()
{
	
	if (!IsValid(MultiplayerSubsystem))
		return;
	MultiplayerSubsystem->FindSessions(10000);
}

void UTestMenu::OnHostSessionButtonClicked()
{
	MultiplayerSubsystem->CreateSession(NumPublicConnections, MatchType);
	
}

void UTestMenu::CreateSessionCompleteCallback(bool bSuccess)
{
	if (!GEngine)
		return;
	
	if (bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Create Session Complete Callback Success"));
		UWorld* World = GetWorld();
		if (World)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,FString("Travelling to Map: " + LobbyMapPath));

			const bool exito = World->ServerTravel(LobbyMapPath, TRAVEL_Absolute);
			if (!exito)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ServerTravel failed"));
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Create Session Complete Callback Failed"));
	}
}

void UTestMenu::JoinSessionCompleteCallback(/* FName SessionName,*/ EOnJoinSessionCompleteResult::Type Result)
{
	const auto GameInstance = GetGameInstance();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback reached"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback Result:"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, LexToString(Result));
		
	if (!IsValid(GameInstance) || Result != EOnJoinSessionCompleteResult::Success || !IsValid(MultiplayerSubsystem))
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback Travelling to lobby"));
	
	const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
		return;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback Subsystem found"));
		
	const IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
	if (!SessionInterface.IsValid())
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback SessionInterface found and valid"));
	
	
	FString Address;
	SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UTestMenu::JoinSessionCompleteCallback Address: %s"), *Address));
	
	APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController();
	if (!IsValid(PlayerController))
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback PlayerController found and valid"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UTestMenu::JoinSessionCompleteCallback Travelling to lobby"));
	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}

void UTestMenu::FindSessionCompleteCallback(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,FString("Find Session Complete Callback. SessionResults lenght: " +  FString::FromInt(SessionResults.Num())));
	
	if (!IsValid(MultiplayerSubsystem))
		return;

	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue != MatchType)
		{
			continue;
		}
	
		MultiplayerSubsystem->JoinSession(Result);
	}
}

void UTestMenu::StartSessionCompleteCallback(bool bSuccess)
{
}

void UTestMenu::DestroySessionCompleteCallback(bool bSuccess)
{
}