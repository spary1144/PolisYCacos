// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PolisCacosGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class POLISYCACOS_API UPolisCacosGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	void CreateGameSession();
	void JoinGameSession();
	void LeaveGameSession();
	void FindGameSessions();
	
	
};
