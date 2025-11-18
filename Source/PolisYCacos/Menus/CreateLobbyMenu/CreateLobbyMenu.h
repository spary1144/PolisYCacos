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
	// seguramente en esta clase haga falta algún tipo de struct que le pase settings a la creación de la lobby de steam
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UEditableTextBox> LobbyNameInputTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UEditableTextBox> MaxNumPlayersInputTextBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	FText Text;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> PublicGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> OnlyFriendsGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> CreateGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> BackButton;
	
	FDelegateHandle OnLobbyCreatedDelegateHandle;
	
	bool OnlyFriendsCanJoin;

public:
	
	virtual void NativeConstruct() override;
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void SetGamePublic();
	
	UFUNCTION()
	void SetGameOnlyFriends();
	
	UFUNCTION()
	void CreateGame();
	
	UFUNCTION()
	void BackPressed();
	
	FORCEINLINE TObjectPtr<UTextBlock> GetTextBlock() const { return TextBlock; }
	FORCEINLINE TObjectPtr<UMainButton> GetPublicGameButton() const { return PublicGameButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetOnlyFriendsGameButton() const { return OnlyFriendsGameButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetCreateGameButton() const { return CreateGameButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetBackButton() const { return BackButton; }
	FORCEINLINE FText GetText() const { return Text; }
	FORCEINLINE void SetText(const FText& NewText) { Text = NewText; }
	
	
};
