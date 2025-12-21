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
	GenerateLevel(10); //Lvl Generation algorithm 
}

// Called every frame
void ARoomGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * @brief Generate the first room of a lvl. We choose the init position \n
 * @param None
 * @return void
 */
void ARoomGenerator::GenerateStartPoint()
{
	GenerationMatrix[0][LvlDensity - LvlDensity/2] = 1;
}

/**
 * @brief : Generate normal rooms in our generation matrix, we represent that rooms
 * with the type 2.
 * @param Density Number of rooms to generate
 * @return void
 */
void ARoomGenerator::GenerateRoomDensity(int Density)
{
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

/**
 * @brief Loop the matrix and looking next rooms, we decide the type of walls to generate.
 * @param  none
 * @return void
 */
void ARoomGenerator::WallGeneration()
{
	for (int i = 0; i < LvlDensity; ++i)
	{
		for (int j = 0; j < LvlDensity; ++j)
		{
			if (GenerationMatrix[i][j] == 2 || GenerationMatrix[i][j] == 4)
			{
				int x=0,y=0;
				for (int Orientation = 0; Orientation < 4; ++Orientation)
				{
					if (Orientation == 0) { x=-1; y=0;}
					else if (Orientation == 1){x=0; y=-1;}
					else if (Orientation == 2){x=1; y=0;}
					else if (Orientation == 3){x=0; y=1;}
					
					if (i+x > LvlDensity-1 || i+x < 0 || j+y > LvlDensity-1|| j+y < 0 || i+x < 0)
					{
						GenerateWalls(6, Orientation, i,j);
					}
					else
					{
						if ( GenerationMatrix[i+x][j+y] == 0) 
						{
							GenerateWalls(6, Orientation, i,j);
						}
						else if (GenerationMatrix[i+x][j+y] == 2)
						{
							GenerateWalls(7, Orientation, i,j);
						}
						else if (GenerationMatrix[i+x][j+y] == 3)
						{
							GenerateWalls(8, Orientation, i, j);
						}
						else if (GenerationMatrix[i+x][j+y] == 4 && GenerationMatrix[i][j] != 4 )
						{
							GenerateWalls(7, Orientation, i, j);
						}
					}
				}
			}
		}
	}
}

/**
 * @brief With ratio and position, we check if a new room spawns
 * @param ratio The % of posibilities to spawn a room
 * @param posx  The vertical position in the matrix, where we are going to generate a room
 * @param posy  The horizontal position in the matrix, where we are going to generate a room
 * @return 1 if the room was generated, 0 in other case.
 */
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

/**
 * @brief Spawn two police rooms, where we will have cameras or other utilities for the police role
 * @param none
 * @return none
 */
void ARoomGenerator::SpawnPoliceRooms()
{
	int x=0,y=0;
	//Select last room to connect the police structure
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
	
	// Spawn the police structure, choosing left or right
	GenerationMatrix[x+4][y] = 2;
	GenerationMatrix[x+3][y] = 3; OrientationMatrix[x+3][y] = 3;
	GenerationMatrix[x+1][y] = 3; OrientationMatrix[x+1][y] = 1;
	
	if (LvlDensity / 2 < y)
	{
		GenerationMatrix[x+2][y] = 5; OrientationMatrix[x+2][y] = 3;
		GenerationMatrix[x+2][y-1] = 3; OrientationMatrix[x+2][y-1] = 2;
		GenerationMatrix[x+2][y-2] = 2;
	}
	else
	{
		GenerationMatrix[x+2][y] = 5; OrientationMatrix[x+2][y] = 1;
		GenerationMatrix[x+2][y+1] = 3; OrientationMatrix[x+2][y-1] = 0;
		GenerationMatrix[x+2][y+2] = 2;
	}
	
}

/**
 * @brief This function is the main logic of the generation lvls algorithm
 * @param RoomDensity the number of rooms to create in the lvl
 * @return void
 */
void ARoomGenerator::SpawnRooms(int RoomDensity)
{
	GenerateStartPoint();
	GenerateRoomDensity(RoomDensity);
	SpawnPoliceRooms();
	MergeRooms(RoomDensity);
	WallGeneration();
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

/**
 * 
 * @param Density Number of rooms in lvls. It will be useful to determinate the number of merged rooms x lvl
 */
void ARoomGenerator::MergeRooms(int Density)
{
	int elements = 0, roomsMerged = 0;
	
	//Select the number of unions between rooms
	if (Density <= 10)
	{
		elements = rand() % 2 + 2;
	}
	else if (Density > 10 && Density < 15)
	{
		elements = rand() % 2 + 3;
	}
	else
	{	
		elements = rand() % 2 + 4;
	}
	
	//This part of the algorithm is usefull to select big rooms, 2 -> 4 (is the same type, but we diferenciate it with other number of type) 
	while (roomsMerged < elements)
	{
		for (int i = 0; i < LvlDensity; ++i)
		{
			for (int j = 0; j < LvlDensity; ++j)
			{
				if (GenerationMatrix[i][j] == 2)
				{
					int chanceToCreateADoubleRoom = rand() % 100;
					if (chanceToCreateADoubleRoom <= 20)
					{
						Chaos::Pair<int,int> doubleRoom = CheckNextRoom(i,j);
						if (doubleRoom.First != -1 && doubleRoom.Second != -1)
						{
							GenerationMatrix[doubleRoom.First][doubleRoom.Second] = 4;
							GenerationMatrix[i][j] = 4;
							roomsMerged++;
						}
					}
				}
			}
		}
	}
}

/**
 * @brief Aux function to select the next room able to merge with
 * @param x position vertical - room to check
 * @param y position horizontal - room to check
 * @return the position of the room selected to merge with room [x][y]
 */
Chaos::Pair<int,int> ARoomGenerator::CheckNextRoom(int x, int y)
{
	Chaos::Pair<int,int> position = {-1,-1};
	if (x>0 && x<LvlDensity && y>0 && y<LvlDensity)
	{
		if (GenerationMatrix[x][y-1] == 2)
		{
			position = {x,y-1};
		}
		else if (GenerationMatrix[x][y+1] == 2)
		{
			position = {x,y+1};
		}
		else if (GenerationMatrix[x-1][y] == 2)
		{
			position = {x-1,y};	
		}
		else if (GenerationMatrix[x+1][y] == 2)
		{
			position = {x+1,y};
		}
	}
	return position;
}

/**
 * @brief Find the mesh to set in the parameter node.
 * @param MeshType name of the model to set
 * @param Room pointer to the ARoomParent node
 * @return void
 */
void ARoomGenerator::FindAndSetMesh(const FString& MeshType, const ARoomParent* Room)
{
	auto Mesh = *RoomMeshes.Find(MeshType);
			
	if (IsValid(Mesh.Get()))
	{
		Room->GetMeshComponent()->SetStaticMesh(Mesh);
	}
}

/**
 * @brief Add the node to wall array and spawn it in the world
 * @param type Number of room, to select the mesh lately
 * @param ori Number to multiply 90º with
 * @param posx Vertical position where we are going to spawn the mesh
 * @param posy Horizontal position where we are going to spawn the mesh
 * @return void
 */
void ARoomGenerator::GenerateWalls(const int type, const int ori, const int posx, const int posy)
{
	ARoomParent* NewRoom = GetWorld()->SpawnActor<ARoomParent>(RoomParentSubclass);
	
	check(IsValid(NewRoom));
	Walls.Add(NewRoom);
	Walls.Last()->SetActorLocation(FVector(5000 * posx,5000*posy,10));
	Walls.Last()->setPosition(posx,posy);
	Walls.Last()->setOrientation(ori);
	Walls.Last()->SetActorRotation(FRotator(0,Walls.Last()->getOrientation() * 90,0));
	Walls.Last()->setType(type);
	SetMeshToRoom(type, NewRoom);
}

/**
 * @brief Add the node to ARoomParent matrix and spawn it in the world. Similar to GenerateWalls()
 * @param type Number of room, to select the mesh lately
 * @param ori Number to multiply 90º with
 * @param posx Vertical position where we are going to spawn the mesh
 * @param posy Horizontal position where we are going to spawn the mesh
 * @return void
 */
void ARoomGenerator::GenerateRoom(const int type, const int ori, const int posx, const int posy)
{
	ARoomParent* NewRoom = GetWorld()->SpawnActor<ARoomParent>(RoomParentSubclass);
	
	check(IsValid(NewRoom));
	Rooms[posx].Room[posy] = NewRoom;
	NewRoom->SetActorLocation(FVector(5000 * posx,5000*posy,10));
	Rooms[posx].Room[posy]->setPosition(posx,posy);
	Rooms[posx].Room[posy]->setOrientation(ori);
	NewRoom->SetActorRotation(FRotator(0,Rooms[posx].Room[posy]->getOrientation() * 90,0));
	Rooms[posx].Room[posy]->setType(type);

	SetMeshToRoom(type, NewRoom);
}

/**
 * @brief Using FindAndSetMesh(int type, ARoomParent* Room) to find and set models to nodes depending on the type of node.
 * @param type Number to select the model to use
 * @param Room Node ARoomParent
 * @return void
 */
void ARoomGenerator::SetMeshToRoom(int type, ARoomParent* Room)
{
	switch (type)
	{
	case 1:
		FindAndSetMesh("First", Room);
		break;
	case 2:
		FindAndSetMesh("Normal", Room); 
		break;
	case 3:
		FindAndSetMesh("Corridor", Room); 
		break;
	case 4:
		FindAndSetMesh("Double room", Room);
		break;
	case 5:
		FindAndSetMesh("Crossing", Room);
		break;
	case 6:
		FindAndSetMesh("Wall", Room);
		break;
	case 7:
		FindAndSetMesh("Open wall", Room);
		break;
	case 8:
		FindAndSetMesh("Wall door", Room);
		break;
	default:
		
		break;
	}
}

/**
 * @brief Prepare the wall array and rooms matrix for the lvl, then start with the algorithm "SpawnRooms"
 * @param RoomDensity Number of rooms to generate
 * @return void
 */
void ARoomGenerator::GenerateLevel(int RoomDensity)
{
	UWorld* World = GetWorld();
	check(World);
	
	Rooms.Empty();
	Rooms.Init(FArrayRooms{},LvlDensity);
	Walls.Empty();
	Walls.Init(nullptr,(RoomDensity+6)*4);
	SpawnRooms(RoomDensity);
}
