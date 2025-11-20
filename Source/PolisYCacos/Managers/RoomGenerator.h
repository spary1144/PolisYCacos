// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PolisYCacos/RoomElements/RoomParent.h"
#include "RoomGenerator.generated.h"

USTRUCT()
struct FArrayRooms
{
	GENERATED_BODY()
	TArray<TObjectPtr<ARoomParent>> Room;
};
UCLASS()
class POLISYCACOS_API ARoomGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> RoomParentSubclass;
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TArray<FArrayRooms> Rooms;
};
