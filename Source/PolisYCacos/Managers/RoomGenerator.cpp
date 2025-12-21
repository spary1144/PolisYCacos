// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGenerator.h"

#include <iostream>

/**
 * @brief Constructor - Prepare the GenerationMatrix and Rooms
 * @param None
 * @return void
 */
ARoomGenerator::ARoomGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GenerationMatrix[LvlDensity][LvlDensity] = {0};
	OrientationMatrix[LvlDensity][LvlDensity] = {0};
	ConstructorHelpers::FClassFinder<ARoomParent> Finder(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Rooms/BP_RoomParent.BP_RoomParent_C'"));

	if (Finder.Succeeded())
	{
		RoomParentSubclass = Finder.Class;
	}
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

/**
 * @brief Generate the first room of a lvl. Randomly, chooses the matrix position. \n
 * @param None
 * @return void
 */
void ARoomGenerator::GenerateStartPoint()
{
	GenerationMatrix[0][LvlDensity - LvlDensity/2] = 1;
}

/**
 * @brief : Generate normal rooms in our generation matrix
 * @param Density Number of rooms to generate
 * @return void
 */
void ARoomGenerator::GenerateRoomDensity(int Density)
{
	/*int RoomsCreated = 0;
	while (RoomsCreated < Density)
	{
		int32 r{}, c{};
		r = rand() % LvlDensity;
		c = rand() % LvlDensity;
		if (GenerationMatrix[r][c] != 1 && GenerationMatrix[r][c] != 2)
		{
			GenerationMatrix[r][c] = 2;
			RoomsCreated++;
		}
	}*/
	
	int elements = 0;
	int ratio = 50;
	while (elements < Density)
	{
		for (int x = 0; x < LvlDensity && elements < Density; ++x)
		{
			for (int y = 0; y < LvlDensity && elements < Density; ++y)
			{
				if (GenerationMatrix[x][y]!=0)
				{
					if (y - 1 > 0 && GenerationMatrix[x][y-1] == 0 && elements < Density)
					{
						elements += PutRoom(ratio, x, y - 1);
						
					}
					else if (y + 1 < LvlDensity && GenerationMatrix[x][y+1] == 0 && elements < Density)
					{
						elements += PutRoom(ratio, x, y + 1);
					}
					else if (x - 1 > 0 && GenerationMatrix[x-1][y] == 0 && elements < Density)
					{
						elements += PutRoom(ratio, x - 1, y);
					}
					else if (x + 1 < LvlDensity && GenerationMatrix[x+1][y] == 0 && elements < Density)
					{
						elements += PutRoom(ratio, x + 1, y);
					}
				}
			}
		}
		if (elements > LvlDensity/2)
		{
			ratio = 33;
		}
	}
}

int ARoomGenerator::PutRoom(int ratio, int posx, int posy)
{
	int room = rand() % 100;
	if (room < ratio)
	{
		GenerationMatrix[posx][posy] = 2;
		return 1;
	}
	return 0;
}

void ARoomGenerator::SpawnPoliceRooms()
{
	int x=0,y=0;
	for (int i = 0; i < LvlDensity; ++i)
	{
		for (int j = 0; j < LvlDensity; ++j)
		{
			if (GenerationMatrix[i][j] != 0)
			{
				x = i; y = j;
			}
		}
	}
	GenerationMatrix[x+4][y] = 2;
	GenerationMatrix[x+3][y] = 3;
	GenerationMatrix[x+2][y] = 3;
	GenerationMatrix[x+1][y] = 3;
}
/**
 * @brief Generate corridors between rooms \n
 *        - Step 1: Generate corridors between rooms \n
 *        - Step 2: Generate more corridors, 50% chance to create a new corridor for each room
 * @param None
 * @return void
 */
void ARoomGenerator::GenerateCorridors()
{
	int prevX = -1, prevY = -1;
	for (int i=0; i < LvlDensity; ++i)
	{
		for (int j=0; j < LvlDensity; ++j)
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
						{
							GenerationMatrix[x][y] = 3;
							OrientationMatrix[x][y] = 1;
						}
					}

					// move h
					while (y != j)
					{
						y += (j > y ? 1 : -1);
						if (GenerationMatrix[x][y] == 0)
						{
							GenerationMatrix[x][y] = 3;
						}
					}
				}

				// Last point
				prevX = i;
				prevY = j;
			}
		}
	}
	//2nd scan to add new Corridors between rooms
	for (int i = 0; i < LvlDensity; ++i)
    {
        for (int j = 0; j < LvlDensity; ++j)
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
                        for (int x = 0; x < LvlDensity; ++x)
                        {
                            for (int y = 0; y < LvlDensity; ++y)
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
                                        {
	                                        GenerationMatrix[px][py] = 3;
                                        	OrientationMatrix[px][py] =1;
                                        }
                                    }

                                    // Horizontal corridor
                                    while (py != y)
                                    {
                                        py += (y > py ? 1 : -1);
                                        if (GenerationMatrix[px][py] == 0)
                                        {
	                                        GenerationMatrix[px][py] = 3;
                                        }
                                    }
	                                
                                    x = LvlDensity; // break x for
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

/**
 *@brief Generate a complete level
 * - Generate start point
 * - Generate rooms ramdomly
 * - Generate corridors
 * 
 * Types of rooms:
 * - Start Room (1)
 * - Normal Rooms (2)
 * - Corridor (3)
 * @param RoomDensity Number of rooms for each generated lvl
 * @return void
 */
/*void ARoomGenerator::GenerateLevel(int RoomDensity)
{
	//Generate Start point
	GenerateStartPoint();
	//Generate Room Density
	GenerateRoomDensity(RoomDensity);
	//Generate Corridors
	GenerateCorridors();
}*/

void ARoomGenerator::GenerateLevel(int RoomDensity)
{
	GenerateStartPoint();
	GenerateRoomDensity(RoomDensity);
	SpawnPoliceRooms();
	int a=0;
}

void ARoomGenerator::FindAndSetMesh(const FString& MeshType, const ARoomParent* Room)
{
	auto Mesh = *RoomMeshes.Find(MeshType);
			
	if (IsValid(Mesh.Get()))
	{
		Room->GetMeshComponent()->SetStaticMesh(Mesh);
	}
}

void ARoomGenerator::GenerateRoom(const int type, const int ori, const int posx, const int posy)
{
	ARoomParent* NewRoom = GetWorld()->SpawnActor<ARoomParent>(RoomParentSubclass);
	
	check(IsValid(NewRoom));
	Rooms[posx].Room[posy] = NewRoom;
	NewRoom->SetActorLocation(FVector(5000 * posx,5000*posy,0));
	Rooms[posx].Room[posy]->setPosition(posx,posy);
	Rooms[posx].Room[posy]->setOrientation(ori);
	NewRoom->SetActorRotation(FRotator(0,Rooms[posx].Room[posy]->getOrientation() * 90,0));
	Rooms[posx].Room[posy]->setType(type);

	switch (type)
	{
		case 1:
			FindAndSetMesh("First", NewRoom);
		break;
		case 2:
			FindAndSetMesh("Normal", NewRoom); 
		break;
		case 3:
			FindAndSetMesh("Corridor", NewRoom); 
		break;
		case 4:
			FindAndSetMesh("Corridor Corner", NewRoom);
		break;
		case 5:
			FindAndSetMesh("Crossing", NewRoom);
		break;
	default:
		
		break;
	}
}

/**
 * @brief Printing blueprints for each room or corridor RED(1), BLUE(2), BLACK(3)
 * @param None
 * @return void
 */
void ARoomGenerator::SpawnRooms()
{
	UWorld* World = GetWorld();
	check(World);
	
	Rooms.Empty();
	Rooms.Init(FArrayRooms{},LvlDensity);
	GenerateLevel(10);
	//CheckOrientation();
	for (int32 i=0; i < LvlDensity;++i)
	{
		Rooms[i].Room.Init(nullptr,LvlDensity);
		for (int32 j=0; j<LvlDensity;++j)
		{
			//probar makeshared
			if (!IsValid(RoomParentSubclass))
				continue;
			if (GenerationMatrix[i][j] != 0)
				GenerateRoom(GenerationMatrix[i][j], OrientationMatrix[i][j], i,j);
		}
	}
}

void ARoomGenerator::CheckOrientation()
{
	int top, bottom, left, right, roomNext;
	int cont = 0;
	top = bottom = left = right = roomNext =0;
	for (int32 i=0; i < LvlDensity;++i)
	{
		for (int32 j=0; j<LvlDensity;++j)
		{
			cont = top = bottom = left = right = 0;
			if (GenerationMatrix[i][j] == 3) //Is a corridor
			{
				if ((GenerationMatrix[i-1][j] != 0 && GenerationMatrix[i-1][j] !=3 && GenerationMatrix[i-1][j] !=5) ||
					(GenerationMatrix[i+1][j] != 0 && GenerationMatrix[i+1][j] !=3 && GenerationMatrix[i+1][j] !=5) ||
					(GenerationMatrix[i][j-1] != 0 && GenerationMatrix[i][j-1] !=3 && GenerationMatrix[i][j-1] !=5) ||
					(GenerationMatrix[i][j+1] != 0 && GenerationMatrix[i][j+1] !=3 && GenerationMatrix[i][j+1] !=5) )
				{
					roomNext = 1;
				}

				if (roomNext == 1) //Hay una habitacion que no es pasillo ni cruce en uno de los lados
				{
					if (GenerationMatrix[i-1][j] != 0 && GenerationMatrix[i-1][j] != 5)
					{
						top = 1;cont++;
					}
					if (GenerationMatrix[i+1][j] != 0 && GenerationMatrix[i+1][j] != 5)
					{
						bottom = 1;cont++;
					}
					if (GenerationMatrix[i][j-1] != 0 && GenerationMatrix[i][j-1] != 5)
					{
						left = 1;cont++;
					}
					if (GenerationMatrix[i][j+1] != 0 && GenerationMatrix[i][j+1] != 5)
					{
						right = 1;cont++;
					}
					
					if (cont == 4)
					{
						//crossing
						GenerationMatrix[i][j] = 5;
					}
					else if (cont == 3)
					{
						//crossing -1 side
						GenerationMatrix[i][j] = 5;
					}
					else if (cont == 2)
					{
						if (left && top)
						{
							GenerationMatrix[i][j] = 4;
							OrientationMatrix[i][j] = 1;
						}
						else if (left && bottom)
						{
							GenerationMatrix[i][j] = 4;
							OrientationMatrix[i][j] = 0;
						}
						else if (right && top)
						{
							GenerationMatrix[i][j] = 4;
							OrientationMatrix[i][j] = 0;
						}
						else if (right && bottom)
						{
							GenerationMatrix[i][j] = 4;
							OrientationMatrix[i][j] = 2;
						}
					}
				}
			}
		}
	}
}