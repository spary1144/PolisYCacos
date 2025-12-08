#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PolisCacosGamemode.generated.h"

class UUserWidget;

UCLASS()
class POLISYCACOS_API APolisCacosGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta =(AllowPrivateAccess="true") )
	TSubclassOf<UUserWidget> MainMenuWidgetSubclass; 
	
public:
	
	virtual void BeginPlay() override;
		
};
