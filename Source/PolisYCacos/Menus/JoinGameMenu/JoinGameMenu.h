#pragma once

#include "Blueprint/UserWidget.h"
#include "JoinGameMenu.generated.h"

class ULobbyWidgetButton;
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
	* - Va a hacer falta un custom widget para representar la info que llegue de los servidores disponibles de steam
	*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UEditableTextBox> LobbyIdInputTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UMainButton> RefreshButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UMainButton> BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LobbyWidgetClass;
	
public:
	
	UFUNCTION()
	void RefreshButtonClicked();
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void FillScrollBox() const;

	FORCEINLINE TObjectPtr<UMainButton> GetRefreshButton() const	{ return RefreshButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetBackButton() const		{ return BackButton; }
	FORCEINLINE TObjectPtr<UEditableTextBox> GetLobbyIdInputTextBox() const	{ return LobbyIdInputTextBox; }
	FORCEINLINE TObjectPtr<UScrollBox> GetScrollBox() const { return ScrollBox; }
	FORCEINLINE TObjectPtr<UTextBlock> GetTextBlock() const { return TextBlock; }
	FORCEINLINE FText GetText() const { return Text; }
	FORCEINLINE void SetText(const FText& NewText) { Text = NewText; }
	
};
