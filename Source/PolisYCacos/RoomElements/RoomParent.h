// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/MapErrors.h"
#include "RoomParent.generated.h"
struct Position{int x; int y;};
UCLASS()
class POLISYCACOS_API ARoomParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomParent();
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMeshComponent() const
	{
		return RoomMesh;
	} 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = Mesh, DisplayName = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> RoomMesh;
	int orientation;
	int typeOfRoom;
	Position position;
public:	
	// Called every frame
	void setPosition(int x, int y);
	Position getPosition();
	void setType(int type);
	int getType();
	void setOrientation(int ori);
	int getOrientation();
	
	virtual void Tick(float DeltaTime) override;

};
