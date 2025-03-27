#include "Player/MOPlayerController.h"
#include "UI/MOChatInput.h"
#include "Kismet/KismetSystemLibrary.h"


void AMOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UMOChatInput>(this, ChatInputWidgetClass);
		
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void AMOPlayerController::SetChatMessageString(const FString& _inChatMessageString)
{
	ChatMessageString = _inChatMessageString;

	PrintChatMesageString(ChatMessageString);
}

void AMOPlayerController::PrintChatMesageString(const FString& _inChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
}
