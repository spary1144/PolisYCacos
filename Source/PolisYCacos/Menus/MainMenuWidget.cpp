// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

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
	
}

void UMainMenu::SettingsPressed()
{
}

void UMainMenu::CreditsPressed()
{
}

void UMainMenu::ExitPressed()
{
}
