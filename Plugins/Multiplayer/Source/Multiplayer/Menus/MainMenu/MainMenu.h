#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Multiplayer/Menus/PlayMenu/PlayMenu.h"
#include "MainMenu.generated.h"

class UCanvasPanel;
class UButton;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
	/**
	 * Components of the menu
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlayButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreditsButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> MainMenuButtonsVerticalBox;
	
	// Ptrs and classes to manage visibilities and stuff
	
	//TObjectPtr<UUserWidget> CurrentMenu;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPlayMenu> PlayMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu subclasses", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayMenuClass;
/*
	UPROPERTY() 
	TObjectPtr<UUserWidget> SettingsMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TSubclassOf<UUserWidget> SettingsMenuClass;

	UPROPERTY() 
	TObjectPtr<UUserWidget> CreditsMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TSubclassOf<UUserWidget> CreditsClass;
*/
	// If we want to create a modal message o algo asi
	//TObjectPtr<UUserWidget> ExitMenu;
	
public:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

	UFUNCTION()
	void PlayMenuBackButtonPressed();

	UFUNCTION()
	void PlayButtonClicked();
	
	UFUNCTION()
	void SettingsButtonClicked();
	
	UFUNCTION()
	void CreditsButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
	
	FORCEINLINE TObjectPtr<UButton> GetPlayButton()     const   { return PlayButton;     }
	FORCEINLINE TObjectPtr<UButton> GetSettingsButton() const	{ return SettingsButton; }
	FORCEINLINE TObjectPtr<UButton> GetCreditsButton()  const	{ return CreditsButton;  }
	FORCEINLINE TObjectPtr<UButton> GetExitButton()     const	{ return ExitButton;		}
};
