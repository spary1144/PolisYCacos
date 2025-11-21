#include "PolisCacosGamemode.h"

#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

void APolisCacosGamemode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (IsValid(PlayerController))
	{
		const FInputModeUIOnly InputMode;
	
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}
	UOnlineInterface::Get();
}
