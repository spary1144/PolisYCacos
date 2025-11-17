#pragma once

#include "Blueprint/UserWidget.h"
#include "JoinGameMenu.generated.h"

class UMainButton;
class UScrollBox;
class UTextBlock;
class UEditableTextBox;

UCLASS()
class UJoinGameMenu : public UUserWidget
{
	GENERATED_BODY()
	/*
	* Join game -> El jugador puede meter a mano el id de la lobby creada para unirse directamente. 
	* - Crear un menú de input para poder insertar el id de la lobby a la que te quieres meter
	* - Mostrar lista de servidores (scroll box)
	* - Botón de refrescar (imagino que llamará a alguna función de steam para tener todas las partidas
	* - Botón de back to menu 
	* - Algún filtro...
	*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UEditableTextBox> LobbyIdInputTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> RefreshButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> BackButton;

public:
	
	virtual void NativeConstruct() override;
	
};
