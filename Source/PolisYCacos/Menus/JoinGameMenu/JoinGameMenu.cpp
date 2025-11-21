#include "JoinGameMenu.h"

#include "Components/ScrollBox.h"
#include "PolisYCacos/Menus/LobbyWidgetButton/LobbyWidgetButton.h"
#include "PolisYCacos/Menus/MainButton/MainButton.h"
#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

void UJoinGameMenu::RefreshButtonClicked()
{
	FillScrollBox();
}

void UJoinGameMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GetRefreshButton()->GetButton()->OnClicked.AddDynamic(this, &UJoinGameMenu::RefreshButtonClicked);
}

void UJoinGameMenu::FillScrollBox() const
{
	const TObjectPtr<UOnlineInterface> OnlineInterface = UOnlineInterface::Get();
	OnlineInterface->FindGameSessions();
	TArray<FOnlineSessionSearchResult> Results = OnlineInterface->GetSearchResults();
	
	if (Results.Num() == 0)
	{
		// Esto hay que pasarlo a widget
		UE_LOG(LogTemp, Warning, TEXT("No hay resultados en la lista de partidas"));
		return;
	}
	
	for (auto& Result : Results)
	{
		ULobbyWidgetButton* Widget = CreateWidget<ULobbyWidgetButton>(GetWorld(), LobbyWidgetClass);
		if (!Widget)
		{
			continue;
		}
		FString LobbyName;
		
		if (!Result.Session.SessionSettings.Get("LOBBY_NAME", LobbyName))
		{
			LobbyName = Result.Session.OwningUserName; 
		}
		const int32 MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
		const int32 OpenSlots  = Result.Session.NumOpenPublicConnections;
		const int32 CurrentPlayers = MaxPlayers - OpenSlots;
		
		const FText LobbyNameText		  = FText::FromString(LobbyName);
		const FText LobbyPopulationText	  = FText::AsNumber(CurrentPlayers);
		const FText MaxPlayerText		  = FText::FromString(FString::FromInt(MaxPlayers));
		
		FText LobbyPopulation = FText::Format(FText::FromString("{0}/{1}"), LobbyPopulationText, MaxPlayerText);
		
		Widget->SetLobbyInfo(LobbyNameText, LobbyPopulation);
		GetScrollBox()->AddChild(Widget);
	}
}
