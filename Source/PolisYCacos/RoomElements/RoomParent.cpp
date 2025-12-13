// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomParent.h"

/**
 * @brief Constructor - Choose the Room mesh
 */
ARoomParent::ARoomParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RoomMesh = CreateDefaultSubobject<UStaticMeshComponent>("RoomMesh");
	RoomMesh->SetupAttachment(GetRootComponent());
	orientation = typeOfRoom = 1;
	position.x = 0;
	position.y = 0;
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

int ARoomParent::getOrientation()
{
	return orientation;
}

Position ARoomParent::getPosition()
{
	return position;
}

int ARoomParent::getType()
{
	return typeOfRoom;
}

void ARoomParent::setType(int type)
{
	typeOfRoom = type;
}

void ARoomParent::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void ARoomParent::setOrientation(int ori)
{
	orientation = ori;
}