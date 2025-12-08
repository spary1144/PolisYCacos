#include "JoinGameMenu.h"

#include "Components/ScrollBox.h"
#include "PolisYCacos/GameInstance/PolisCacosGameInstance.h"
#include "PolisYCacos/Menus/LobbyWidgetButton/LobbyWidgetButton.h"
#include "PolisYCacos/Menus/MainButton/MainButton.h"
#include "PolisYCacos/OnlineInterface/OnlineInterface.h"


void UJoinGameMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GetRefreshButton()->GetButton()->OnClicked.AddDynamic(this, &UJoinGameMenu::RefreshButtonClicked);
	GameInstance = CastChecked<UPolisCacosGameInstance>(GetGameInstance());
	BindToGameInstanceDelegate();
}

void UJoinGameMenu::RefreshButtonClicked()
{
}

void UJoinGameMenu::BindToGameInstanceDelegate()
{

}

void UJoinGameMenu::FillScrollBox()
{
}
