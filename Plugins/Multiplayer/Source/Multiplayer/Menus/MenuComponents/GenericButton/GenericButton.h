#pragma once
#include "Components/Button.h"
#include "GenericButton.generated.h"

UCLASS()
class MULTIPLAYER_API UGenericButton : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	FText HoverText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> Button;

public: 
	
	TObjectPtr<UButton> GetButton() const { return Button; }
	
};
