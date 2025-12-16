#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Multiplayer/Menus/MenuComponents/GenericButton/GenericButton.h"
#include "JoinLobbyButton.generated.h"

UCLASS()
class MULTIPLAYER_API UJoinLobbyButton : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	FText LobbyName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UGenericButton> JoinButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	FText Ping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	FText LobbyPopulation;
	
public: 
	
	FORCEINLINE void SetLobbyName(const FText& LobbyNameText) { LobbyName = LobbyNameText; };
	FORCEINLINE void SetPing(const FText& PingText) { Ping = PingText; };
	FORCEINLINE void SetLobbyPopulation(const FText& LobbyPopulationText) { LobbyPopulation = LobbyPopulationText; };	
	
};
