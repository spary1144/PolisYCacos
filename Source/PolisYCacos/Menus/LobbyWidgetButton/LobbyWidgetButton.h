#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetButton.generated.h"

class UTextBlock;
class UMainButton;

UCLASS()
class ULobbyWidgetButton: public UUserWidget
{
	GENERATED_BODY()
	// añadir también un num para el ping de la partida
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> LobbyName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> LobbyPopulation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UMainButton> JoinButton;
	
public:
	
	void SetLobbyInfo(const FText& LobbyNameText, const FText& LobbyPopulationText) const;
	
	virtual void NativeOnInitialized() override;
	
};