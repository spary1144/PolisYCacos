// Fill out your copyright notice in the Description page of Project Settings.


#include "PolisCacosGameInstance.h"

#include "PolisYCacos/OnlineInterface/OnlineInterface.h"

void UPolisCacosGameInstance::Init()
{
	Super::Init();
	UOnlineInterface::Get();
}

void UPolisCacosGameInstance::CreateGameSession()
{
	
}

void UPolisCacosGameInstance::JoinGameSession()
{
}

void UPolisCacosGameInstance::LeaveGameSession()
{
}

void UPolisCacosGameInstance::FindGameSessions()
{
}
