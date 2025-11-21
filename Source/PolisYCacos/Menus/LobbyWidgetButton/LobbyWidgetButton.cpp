#include "LobbyWidgetButton.h"

#include "Components/TextBlock.h"

void ULobbyWidgetButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void ULobbyWidgetButton::SetLobbyInfo(const FText& LobbyNameText, const FText& LobbyPopulationText) const
{
	if (LobbyNameText.IsEmpty() || LobbyPopulationText.IsEmpty() || !LobbyName || !LobbyPopulation)
	{
		return;
	}
	
	LobbyName->SetText(LobbyNameText);
	LobbyPopulation->SetText(LobbyPopulationText);
	
}
