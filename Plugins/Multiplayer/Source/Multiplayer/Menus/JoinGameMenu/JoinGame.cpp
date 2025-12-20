#include "JoinGame.h"
#include "OnlineSessionSettings.h"

void UJoinGame::InitializeGamelist()
{
	
}

void UJoinGame::RefreshButtonClicked()
{
	
}

void UJoinGame::FillScrollBox(const TArray<FOnlineSessionSearchResult>& SessionResults)
{
	for (auto Result : SessionResults)
	{
		if (!Result.IsValid())
		{
			continue;
		}
		TObjectPtr<UWidget> Widget = CreateWidget<UUserWidget>(GetWorld(), LobbyWidgetClass);
	}
}
