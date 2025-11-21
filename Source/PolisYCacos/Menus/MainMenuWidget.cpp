// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "CreateLobbyMenu/CreateLobbyMenu.h"
#include "JoinGameMenu/JoinGameMenu.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::CreateJoinGamePressed()
{
	UJoinGameMenu* CreateLobbyMenu = CreateWidget<UJoinGameMenu>(GetWorld(), JoinGameMenuSubclass);
	if (CreateLobbyMenu)
	{
		CreateLobbyMenu->AddToViewport();
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainMenu::CreateCreateGamePressed()
{
	UCreateLobbyMenu* CreateGameMenu = CreateWidget<UCreateLobbyMenu>(GetWorld(), CreateLobbyMenuSubclass);
	if (CreateGameMenu)
	{
		CreateGameMenu->AddToViewport();
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// Ejemplo para bindear los botones pal laure (y pa quien lo vea)
	//GetMainButton()->GetButton()->OnClicked.AddDynamic();
	GetPlayButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::PlayPressed);
	GetExitButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::ExitPressed);
	GetCreditsButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::CreditsPressed);
	GetSettingsButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::SettingsPressed);
	GetCreateJoinGameMenu()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::CreateJoinGamePressed);
	GetCreateCreateGameMenu()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::CreateCreateGamePressed);
	GetChooseModeVerticalBox()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::PlayPressed()
{
	// Abrir un GameMenu
	GetChooseModeVerticalBox()->SetVisibility(ESlateVisibility::Visible);
	GetMainVerticalBox()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::SettingsPressed()
{
	// Abrir menu de settings
}

void UMainMenu::CreditsPressed()
{
	// Abrir menu de creditos
}

void UMainMenu::ExitPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}