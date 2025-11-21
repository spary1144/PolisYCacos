#include "LobbyManager.h"
#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

TObjectPtr<ULobbyManager> ULobbyManager::Instance = nullptr;

void ULobbyManager::BeginDestroy()
{
	UObject::BeginDestroy();
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(LobbyOpenedDelegateHandle);
	LobbyOpenedDelegateHandle.Reset();
}

void ULobbyManager::PostLobbyOpened(UWorld* World)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(LobbyOpenedDelegateHandle);
	LobbyOpenedDelegateHandle.Reset();
	const TObjectPtr<UOnlineInterface> OnlineSessionPtr = UOnlineInterface::Get();
	if (!OnlineSessionPtr)
	{
		return;
	}

	// Aqui ya está creada la lobby y en principio se puede unir la gente a la partida
	OnlineSessionPtr->CreateGameSession(GetNumMaxPlayers(), GetLobbyName(), GetOnlyFriendsCanJoin());
}

