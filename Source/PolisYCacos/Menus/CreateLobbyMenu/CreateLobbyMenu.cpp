#include "CreateLobbyMenu.h"

#include "PolisYCacos/GameInstance/PolisCacosGameInstance.h"
#include "PolisYCacos/Menus/MainButton/MainButton.h"

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
	// Pasos:
	// Llamar al game instance para que las funciones qwue tiene dentro gestionen las movidas
	UPolisCacosGameInstance* GameInstance = Cast<UPolisCacosGameInstance>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance Invalid"));
		return;
	}
	
	//(int32 MaxPlayers, const FString& LobbyName, bool bOnlyFriends)
}

void UCreateLobbyMenu::BackPressed()
{
	
}
