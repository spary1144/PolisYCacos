#include "CreateLobbyMenu.h"

#include "Kismet/GameplayStatics.h"
#include "PolisYCacos/Managers/LobbyManager.h"
#include "PolisYCacos/Menus/MainButton/MainButton.h"
#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

void UCreateLobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCreateLobbyMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GetPublicGameButton()->GetButton()->OnClicked.AddDynamic(this, &ThisClass::SetGamePublic);
	GetOnlyFriendsGameButton()->GetButton()->OnClicked.AddDynamic(this, &ThisClass::SetGameOnlyFriends);
	GetCreateGameButton()->GetButton()->OnClicked.AddDynamic(this, &ThisClass::CreateGame);
	GetBackButton()->GetButton()->OnClicked.AddDynamic(this, &ThisClass::BackPressed);
	
}

void UCreateLobbyMenu::SetGamePublic()
{
	OnlyFriendsCanJoin = false;
}

void UCreateLobbyMenu::SetGameOnlyFriends()
{
	OnlyFriendsCanJoin = true;
}

void UCreateLobbyMenu::CreateGame()
{
	const TObjectPtr<ULobbyManager> LobbyManager = ULobbyManager::Get();
	if (!LobbyManager)
	{
		return;
	}
	
	LobbyManager->SetNumMaxPlayers(FCString::Atoi(*MaxNumPlayersInputTextBox->GetText().ToString()));
	LobbyManager->SetLobbyName(LobbyNameInputTextBox->GetText().ToString());
	LobbyManager->SetOnlyFriendsCanJoin(OnlyFriendsCanJoin);
	
	LobbyManager->LobbyOpenedDelegateHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(LobbyManager, &ULobbyManager::PostLobbyOpened);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_Lobby"));
}

void UCreateLobbyMenu::BackPressed()
{
	
}
