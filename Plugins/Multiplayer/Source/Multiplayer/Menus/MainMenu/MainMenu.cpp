#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Multiplayer/Menus/PlayMenu/PlayMenu.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);
	
	const UWorld* World = GetWorld();
	check(IsValid(World));
	
	const TObjectPtr<APlayerController> PlayerController = World->GetFirstPlayerController();
	check(IsValid(PlayerController));
	
	FInputModeUIOnly InputModeData;
	//InputModeData.SetWidgetToFocus(TakeWidget());
	PlayerController->SetShowMouseCursor(true);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::MenuSetup()
{
	// Buttons binding
	GetPlayButton()->OnClicked.AddDynamic(this, &ThisClass::PlayButtonClicked);
	GetSettingsButton()->OnClicked.AddDynamic(this, &ThisClass::SettingsButtonClicked);
	GetCreditsButton()->OnClicked.AddDynamic(this, &ThisClass::CreditsButtonClicked);
	GetExitButton()->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	
	//PlayMenu	 = CreateWidget<UPlayMenu>(this, PlayMenuClass);
	//SettingsMenu = CreateWidget<USettingsMenu>(this, SettingsMenuClass);
	//CreditsMenu = CreateWidget<UCreditsMenu>(this, CreditsClass);
	
	if (!IsValid(PlayMenu) /*|| !IsValid(SettingsMenu) || !IsValid(CreditsMenu)*/)
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenu: Failed to create menu widgets"));
		return;
	}
	
	PlayMenu->SetVisibility(ESlateVisibility::Collapsed);
	//PlayMenu->AddToViewport();
	PlayMenu->GetBackButton()->OnPressed.AddDynamic(this, &ThisClass::PlayMenuBackButtonPressed);
	PlayMenu->MenuSetup(4, "Match", "PathToLobby" );

}

void UMainMenu::PlayMenuBackButtonPressed()
{
	PlayMenu->HidePlayMenu();
	MainMenuButtonsVerticalBox->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenu::PlayButtonClicked()
{
	PlayMenu->SetVisibility(ESlateVisibility::Visible);
	PlayMenu->ShowPlayMenu();
	MainMenuButtonsVerticalBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::SettingsButtonClicked()
{
	
}

void UMainMenu::CreditsButtonClicked()
{
	
}

void UMainMenu::ExitButtonClicked()
{
	
}
