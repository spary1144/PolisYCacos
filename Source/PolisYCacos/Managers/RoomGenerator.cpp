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
	GenerationMatrix[10][10] = {0};
}

// Called when the game starts or when spawned
void ARoomGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnRooms();
}

// Called every frame
void ARoomGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
 * 1 - Start Room
 * 2 - Normal Rooms
 * 3 - Corridor
 */

void ARoomGenerator::GenerateLevel(int RoomDensity)
{
	//Generate Start point
	{
		int border = rand() % 4;

		int row = 0;
		int col = 0;

		switch (border)
		{
			case 0: // up
				row = 0;
				col = rand() % 10;
				break;
			case 1: // down
				row = 9;
				col = rand() % 10;
				break;
			case 2: // left
				row = rand() % 10;
				col = 0;
				break;
			case 3: // right
				row = rand() % 10;
				col = 9;
				break;
			default:
				row =0;
				col = 0;
				break;
		}
		GenerationMatrix[row][col] = 1; //Start position, border
	}
	//Generate Room Density
	{
		int RoomsCreated = 0;
		while (RoomsCreated < RoomDensity)
		{
			int32 r{}, c{};
			r = rand() % 10;
			c = rand() % 10;
			if (GenerationMatrix[r][c] != 1 && GenerationMatrix[r][c] != 2)
			{
				GenerationMatrix[r][c] = 2;
				RoomsCreated++;
			}
		}
	}
	//Generate Corridors
	{
		int prevX = -1, prevY = -1;
		for (int i=0; i < 10; ++i)
		{
			for (int j=0; j < 10; ++j)
			{
				if (GenerationMatrix[i][j] == 1 || GenerationMatrix[i][j] == 2)
				{
					// If we have a previous point, we print a corridor
					if (prevX != -1)
					{
						int x = prevX;
						int y = prevY;

						// move v
						while (x != i)
						{
							x += (i > x ? 1 : -1);
							if (GenerationMatrix[x][y] == 0)
								GenerationMatrix[x][y] = 3;
						}

						// move h
						while (y != j)
						{
							y += (j > y ? 1 : -1);
							if (GenerationMatrix[x][y] == 0)
								GenerationMatrix[x][y] = 3;
						}
					}

					// Last point
					prevX = i;
					prevY = j;
				}
			}
		}
	}
	//2nd scan to add new Corridors between rooms
	{
		for (int i = 0; i < 10; ++i)
	    {
	        for (int j = 0; j < 10; ++j)
	        {
	            // Looking for 1 or 2 
	            if (GenerationMatrix[i][j] == 1 || GenerationMatrix[i][j] == 2)
	            {
	                // Looking for 3
	                int exits = 0;
	                if (i > 0 && GenerationMatrix[i-1][j] == 3) exits++;
	                if (i < 9 && GenerationMatrix[i+1][j] == 3) exits++;
	                if (j > 0 && GenerationMatrix[i][j-1] == 3) exits++;
	                if (j < 9 && GenerationMatrix[i][j+1] == 3) exits++;

	                if (exits == 1) // If only one exit
	                {
	                    if (rand() % 2 == 1) // 50% popssibility to insert new corridor
	                    {
	                        // Looking for another 2 to conect
	                        for (int x = 0; x < 10; ++x)
	                        {
	                            for (int y = 0; y < 10; ++y)
	                            {
	                                if (GenerationMatrix[x][y] == 2 && (x != i || y != j))
	                                {
	                                    int px = i;
	                                    int py = j;

	                                    // Vertical corridor
	                                    while (px != x)
	                                    {
	                                        px += (x > px ? 1 : -1);
	                                        if (GenerationMatrix[px][py] == 0)
	                                            GenerationMatrix[px][py] = 3;
	                                    }

	                                    // Horizontal corridor
	                                    while (py != y)
	                                    {
	                                        py += (y > py ? 1 : -1);
	                                        if (GenerationMatrix[px][py] == 0)
	                                            GenerationMatrix[px][py] = 3;
	                                    }
	                                	
	                                    x = 10; // break x for
	                                    break;
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
	    }
	}
}

void ARoomGenerator::SpawnRooms()
{
	Rooms.Empty();
	Rooms.Init(FArrayRooms{},10);
	GenerateLevel(3);
	for (int i=0; i < 10;++i)
	{
		Rooms[i].Room.Init(nullptr,10);
		for (int j=0; j<10;++j)
		{
			//probar makeshared
			if (!IsValid(RoomParentSubclass) || !IsValid(GetWorld()))
				continue;
			if (GenerationMatrix[i][j] == 1 ||GenerationMatrix[i][j] == 2 || GenerationMatrix[i][j] == 3)
			{
				auto AuxPtr  = Cast<ARoomParent>(GetWorld()->SpawnActor<ARoomParent>(RoomParentSubclass));
				if (IsValid(AuxPtr))
				{
					Rooms[i].Room.Add(AuxPtr); 
					if (GenerationMatrix[i][j] == 1 )
					{
						//AuxPtr->GetMeshComponent()->GetStaticMesh()->SetMaterial(0, Colours[0]);
						AuxPtr->GetMeshComponent()->SetMaterial(0, Colours[0]);
					}
					else if (GenerationMatrix[i][j] == 2)
					{
						//AuxPtr->GetMeshComponent()->GetStaticMesh()->SetMaterial(0, Colours[1]);
						AuxPtr->GetMeshComponent()->SetMaterial(0, Colours[1]);
					}
					else if (GenerationMatrix[i][j] == 3)
					{
						//AuxPtr->GetMeshComponent()->GetStaticMesh()->SetMaterial(0, Colours[2]);
						AuxPtr->GetMeshComponent()->SetMaterial(0, Colours[2]);
					}
					AuxPtr->SetActorLocation(FVector(225 * i,225*j,0));
				}
			}
		}
	}
}