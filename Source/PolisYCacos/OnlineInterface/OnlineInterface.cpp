#include "OnlineInterface.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UOnlineInterface* UOnlineInterface::OnlineInterfacePtr = nullptr;

UOnlineInterface::UOnlineInterface()
{
	OnlineSubsystemPtr  = nullptr;
	SessionInterfacePtr = nullptr;
}

void UOnlineInterface::Initialize()
{
	OnlineSubsystemPtr = IOnlineSubsystem::Get();
	
	if (!OnlineSubsystemPtr)
	{
		return;
	}
	SessionInterfacePtr = OnlineSubsystemPtr->GetSessionInterface();
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = false;
	if (!SessionInterfacePtr.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionManager: no se pudo obtener la interfaz de sesión."));
	}
}

UOnlineInterface* UOnlineInterface::Get() 
{
	if (OnlineInterfacePtr == nullptr)
	{
		OnlineInterfacePtr = NewObject<UOnlineInterface>();
		OnlineInterfacePtr->AddToRoot();
		OnlineInterfacePtr->Initialize();
	}
	return OnlineInterfacePtr;
}

IOnlineSessionPtr UOnlineInterface::GetSession()
{
	return nullptr;
	//return SessionInterfacePtr;
}