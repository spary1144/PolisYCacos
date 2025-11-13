#include "MainButton.h"
#include "Components/TextBlock.h"

void UMainButton::NativeConstruct()
{
	UUserWidget::NativeConstruct();
}

void UMainButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (TextBlock && !Text.IsEmpty())
	{
		TextBlock->SetText(Text);
	}
}
