#pragma once
#include "OnlineSubsystem.h"

class OnlineInterface : public UObject
{
public:

	void Initialize();

	static OnlineInterface* Get();

	IOnlineSessionPtr GetSession() const;
	
private:
	
	OnlineInterface();
	
	static OnlineInterface* OnlineInterfacePtr;
	
	IOnlineSubsystem* OnlineSubsystemPtr;
	IOnlineSessionPtr SessionInterfacePtr;
};
