// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomParent.h"

// Sets default values
ARoomParent::ARoomParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RoomMesh = CreateDefaultSubobject<UStaticMeshComponent>("RoomMesh");
	RoomMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ARoomParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

