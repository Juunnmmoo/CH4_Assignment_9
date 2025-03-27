#include "UI/MOChatInput.h"
#include "Components/EditableTextBox.h"
#include "Player/MOPlayerController.h"

void UMOChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UMOChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UMOChatInput::OnChatInputTextCommitted(const FText& _text, ETextCommit::Type _commitMethod)
{
	if (_commitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			AMOPlayerController* OwningMOPlayerController = Cast<AMOPlayerController>(OwningPlayerController);
			if (IsValid(OwningMOPlayerController) == true)
			{
				OwningMOPlayerController->SetChatMessageString(_text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}

