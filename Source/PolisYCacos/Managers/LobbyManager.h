#pragma once
#include "CoreMinimal.h"
#include "LobbyManager.generated.h"
UCLASS()
class ULobbyManager : public UObject
{
	GENERATED_BODY()
	
	ULobbyManager() = default;
	
	int32 NumMaxPlayers		= 4; 
	FString LobbyName		= "PolisCacos";
	bool OnlyFriendsCanJoin = true;
	
	static TObjectPtr<ULobbyManager> Instance;
	
public:
	
	FDelegateHandle LobbyOpenedDelegateHandle;
	
	void Initialize()
	{
		
	};
	
	virtual void BeginDestroy() override;
	
	UFUNCTION()
	void PostLobbyOpened(UWorld* World);
	
	static TObjectPtr<ULobbyManager> Get()
	{
		if (Instance == nullptr)
		{
			Instance = NewObject<ULobbyManager>();
			Instance->AddToRoot();
			Instance->Initialize();
		}
		return Instance;
	};
	
	FORCEINLINE void SetNumMaxPlayers(const int32 NewNumMaxPlayers){ NumMaxPlayers = NewNumMaxPlayers;};
	FORCEINLINE void SetLobbyName(const FString& NewLobbyName){ LobbyName = NewLobbyName;};
	FORCEINLINE void SetOnlyFriendsCanJoin(const bool NewOnlyFriendsCanJoin){ OnlyFriendsCanJoin = NewOnlyFriendsCanJoin;};
	FORCEINLINE int32 GetNumMaxPlayers() const { return NumMaxPlayers;};
	FORCEINLINE FString GetLobbyName() const { return LobbyName;};
	FORCEINLINE bool GetOnlyFriendsCanJoin() const { return OnlyFriendsCanJoin;};
	
};
