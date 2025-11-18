#pragma once
#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineInterface.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateSessionCompleted, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionsCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoinSessionCompleted, bool, bSuccess);

class FOnlineSessionSearch;
class FOnlineSessionSearchResult;

UCLASS()
class UOnlineInterface : public UObject
{
	GENERATED_BODY()
	
	UOnlineInterface();

	FString LobbyID;
	
	static UOnlineInterface* Instance;
	IOnlineSubsystem* OnlineSubsystemPtr;
	IOnlineSessionPtr SessionInterfacePtr;
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	TArray<FOnlineSessionSearchResult> SessionSearchResult;
	
	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnFindSessionComplete(bool bSuccess);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
public:
	
	static UOnlineInterface* Get();
	
	void Initialize();
	
	void CreateGameSession(int32 MaxPlayers, const FString& SessionName, bool OnlyFriendsCanJoin) const;
	void JoinGameSession(int32 Index);
	void JoinGameSession(const FString& SessionID);
	void LeaveGameSession();
	void FindGameSessions();
	void DestroySession();
	
	UPROPERTY(BlueprintAssignable)
	FOnCreateSessionCompleted OnCreateSessionCompleteDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnFindSessionsCompleted OnFindSessionsCompleteDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnJoinSessionCompleted OnJoinSessionCompleteDelegate;
	
	[[nodiscard]] FORCEINLINE const TArray<FOnlineSessionSearchResult>& GetSearchResults() const { return SessionSearchResult; }
	

};
