// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGenerator.h"

// Sets default values
ARoomGenerator::ARoomGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ConstructorHelpers::FClassFinder<ARoomParent> Finder(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Rooms/BP_RoomParent.BP_RoomParent_C'"));
	if (Finder.Succeeded())
		RoomParentSubclass = Finder.Class;
	
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomGenerator::BeginPlay()
{
	Super::BeginPlay();
	Rooms.Empty();
	Rooms.Init(FArrayRooms{},10);
	for (int i=0; i < 10;++i)
	{
		Rooms[i].Room.Init(nullptr,10);
		for (int j=0; j<10;++j)
		{
			//probar makeshared
			if (!IsValid(RoomParentSubclass) || !IsValid(GetWorld()))
				continue;
			
			//auto AuxPtr  = Cast<ARoomParent>(GetWorld()->SpawnActor(RoomParentSubclass));
			auto AuxPtr  = Cast<ARoomParent>(GetWorld()->SpawnActor<ARoomParent>(RoomParentSubclass));
			if (IsValid(AuxPtr))
			{
				Rooms[i].Room.Add(AuxPtr); 
				AuxPtr->SetActorLocation(FVector(250 * i,250*j,10));
			}
		}
	}
}

// Called every frame
void ARoomGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

