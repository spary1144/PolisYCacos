#pragma once
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainButton.generated.h"

class UTextBlock;

UCLASS()
class POLISYCACOS_API UMainButton : public UUserWidget
{
		GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	FORCEINLINE UButton* GetButton() const { return Button; }

	FORCEINLINE void SetButtonText(const FName& NewName)
	{
		Text = FText::FromName(NewName);
	}

	virtual void SynchronizeProperties() override;
		
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BlueprintProtected = "true", BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
};
