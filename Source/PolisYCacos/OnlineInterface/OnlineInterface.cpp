#include "OnlineInterface.h"
#include "OnlineSubsystem.h"

OnlineInterface* OnlineInterface::OnlineInterfacePtr = nullptr;

OnlineInterface::OnlineInterface()
{
	OnlineSubsystemPtr  = nullptr;
	SessionInterfacePtr = nullptr;
}

void OnlineInterface::Initialize()
{
	OnlineSubsystemPtr = IOnlineSubsystem::Get();
	
	if (!OnlineSubsystemPtr)
	{
		return;
	}
	SessionInterfacePtr = OnlineSubsystemPtr->GetSessionInterface();
	if (!SessionInterfacePtr.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionManager: no se pudo obtener la interfaz de sesión."));
	}
}

OnlineInterface* OnlineInterface::Get() 
{
	if (OnlineInterfacePtr == nullptr)
	{
		OnlineInterfacePtr = NewObject<OnlineInterface>();
		OnlineInterfacePtr->AddToRoot();
		OnlineInterfacePtr->Initialize();
	}
	return OnlineInterfacePtr;
}

IOnlineSessionPtr OnlineInterface::GetSession() const
{
	return SessionInterfacePtr;
}
