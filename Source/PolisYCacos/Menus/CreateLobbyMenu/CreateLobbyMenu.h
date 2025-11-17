#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "CreateLobbyMenu.generated.h"

class UTextBlock;
class UMainButton;
class UButton;

UCLASS()
class POLISYCACOS_API UCreateLobbyMenu : public UUserWidget
{
	GENERATED_BODY()

// Botones 
	/*
	 * Host game -> esto debería llevar a menú de crear partida.
	 * - Texto para el input del name
	 * - Input para el nombre de la sala
	 * - Selector de privado o publico
	 * - Botón de confirmar
	 * - Botón de back
	 * - Posibles ajustes extra...
	*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> PublicGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> OnlyFriendsGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> JoinGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> BackButton;

public:
	virtual void NativeConstruct() override;
};
