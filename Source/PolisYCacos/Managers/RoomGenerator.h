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
	TArray<FArrayRooms> Rooms;
private:
	static constexpr short LvlDensity = 11;
	int32 GenerationMatrix[LvlDensity][LvlDensity];
	int8  OrientationMatrix[LvlDensity][LvlDensity];
	void GenerateStartPoint();
	void GenerateRoomDensity(int Density);
	int  PutRoom(int ratio, int posx, int posy);
	void SpawnPoliceRooms();
	void GenerateCorridors();
	void GenerateRoom(const int type, const int ori, const int posx, const int posy);
	void FindAndSetMesh(const FString& MeshType, const ARoomParent* Room);
	void CheckOrientation();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess="true"))
	TSubclassOf<AActor> RoomParentSubclass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess="true"))
	TMap<FString, TObjectPtr<UStaticMesh>> RoomMeshes; 
	
	 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(CallInEditor, DisplayName="GenerateLvl")
	void GenerateLevel(int RoomDensity);
	void PaintMatrix();

	UFUNCTION(CallInEditor, DisplayName="Generate")
	void SpawnRooms();
	
	UPROPERTY(EditAnywhere, Category = "Variables", meta=(AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UMaterial>> Colours;
};
