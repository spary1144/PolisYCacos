// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGenerator.h"

/**
 * @brief Constructor - Prepare the GenerationMatrix and Rooms
 * @param None
 * @return void
 */
ARoomGenerator::ARoomGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GenerationMatrix[10][10] = {0};
	OrientationMatrix[10][10] = {0};
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

/**
 * @brief : Generate normal rooms in our generation matrix
 * @param Density Number of rooms to generate
 * @return void
 */
void ARoomGenerator::GenerateRoomDensity(int Density)
{
	int RoomsCreated = 0;
	while (RoomsCreated < Density)
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
						{
							GenerationMatrix[x][y] = 3;
							OrientationMatrix[x][y] = 1; //orientation (top)
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
                                        {
	                                        GenerationMatrix[px][py] = 3;
                                        	OrientationMatrix[px][py] = 1;
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
void ARoomGenerator::GenerateLevel(int RoomDensity)
{
	//Generate Start point
	GenerateStartPoint();
	//Generate Room Density
	GenerateRoomDensity(RoomDensity);
	//Generate Corridors
	GenerateCorridors();
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
	Rooms.Init(FArrayRooms{},10);
	GenerateLevel(10);
	for (int32 i=0; i < 10;++i)
	{
		Rooms[i].Room.Init(nullptr,10);
		for (int32 j=0; j<10;++j)
		{
			//probar makeshared
			if (!IsValid(RoomParentSubclass))
				continue;
			if (GenerationMatrix[i][j] != 0)
				GenerateRoom(GenerationMatrix[i][j], OrientationMatrix[i][j], i,j);
		}
	}
}