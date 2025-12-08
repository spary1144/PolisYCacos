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
	ARoomGenerator();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> RoomParentSubclass;
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TArray<FArrayRooms> Rooms;
private:
	int32 GenerationMatrix[10][10];
	void GenerateStartPoint();
	void GenerateRoomDensity(int Density);
	void GenerateCorridors();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(CallInEditor, DisplayName="GenerateLvl")
	void GenerateLevel(int RoomDensity);
	
	UFUNCTION(CallInEditor, DisplayName="Generate")
	void SpawnRooms();
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UMaterial>> Colours;
};
