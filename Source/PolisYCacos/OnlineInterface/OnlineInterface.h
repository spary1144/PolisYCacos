#pragma once
#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineInterface.generated.h"

UCLASS()
class UOnlineInterface : public UObject
{
	GENERATED_BODY()
public:
	
	void Initialize();
	static UOnlineInterface* Get();
	static IOnlineSessionPtr GetSession();
	
private:
	
	UOnlineInterface();
	
	static UOnlineInterface* OnlineInterfacePtr;
	IOnlineSubsystem* OnlineSubsystemPtr;
	IOnlineSessionPtr SessionInterfacePtr;

};
