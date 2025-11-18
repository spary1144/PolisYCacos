// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "CreateLobbyMenu/CreateLobbyMenu.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// Ejemplo para bindear los botones pal laure (y pa quien lo vea)
	//GetMainButton()->GetButton()->OnClicked.AddDynamic();
	GetPlayButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::PlayPressed);
	GetExitButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::ExitPressed);
	GetCreditsButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::CreditsPressed);
	GetSettingsButton()->GetButton()->OnClicked.AddDynamic(this, &UMainMenu::SettingsPressed);
}

void UMainMenu::PlayPressed()
{
	// Abrir un GameMenu
	UCreateLobbyMenu* Widget = CreateWidget<UCreateLobbyMenu>(GetWorld(), CreateLobbyMenuSubclass);
	if (!Widget)
	{
		return;
	}
	Widget->AddToViewport();
	SetVisibility(ESlateVisibility::Collapsed);
	
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