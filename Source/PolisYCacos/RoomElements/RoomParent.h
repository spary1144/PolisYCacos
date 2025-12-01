// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/MapErrors.h"
#include "RoomParent.generated.h"

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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
