#include "LobbyManager.h"
#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

TObjectPtr<ULobbyManager> ULobbyManager::Instance = nullptr;

void ULobbyManager::PostLobbyOpened(UWorld* World)
{
	const TObjectPtr<UOnlineInterface> OnlineSessionPtr = UOnlineInterface::Get();
	if (!OnlineSessionPtr)
	{
		return;
	}

	// Aqui ya está creada la lobby y en principio se puede unir la gente a la partida
	OnlineSessionPtr->CreateGameSession(GetNumMaxPlayers(), GetLobbyName(), GetOnlyFriendsCanJoin());
	LobbyOpenedDelegateHandle.Reset();
}