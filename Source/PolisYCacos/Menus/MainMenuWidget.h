// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainButton/MainButton.h"
#include "MainMenuWidget.generated.h"

class UVerticalBox;
class UCanvasPanel;

UCLASS()
class POLISYCACOS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;

	// Funciones de respuesta de los botones de menu
	UFUNCTION()
	void PlayPressed();
	UFUNCTION()
	void SettingsPressed();
	UFUNCTION()
	void CreditsPressed();
	UFUNCTION()
	void ExitPressed();

	// GETTERS WALL
	
	FORCEINLINE UVerticalBox* GetMainVerticalBox() const { return MainVerticalBox; }
	FORCEINLINE UCanvasPanel* GetCanvasPanel() const { return CanvasPanel; }
	//Getters de los botones (Son forceinline, asi podemos llamarlo en la propia clase y no hay problema con ello
	FORCEINLINE TObjectPtr<UMainButton> GetPlayButton() const { return PlayButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetExitButton() const { return ExitButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetCreditsButton() const { return CreditsButton; }
	FORCEINLINE TObjectPtr<UMainButton> GetSettingsButton() const { return SettingsButton; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> PlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> SettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> CreditsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UMainButton> ExitButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UVerticalBox> MainVerticalBox;
	
};
