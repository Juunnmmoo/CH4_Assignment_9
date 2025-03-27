#pragma once

#include "CoreMinimal.h"
#include "Types/SlateEnums.h"
#include "Blueprint/UserWidget.h"
#include "MOChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class ASSIGNMENT9_API UMOChatInput : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditableTextBox_ChatInput;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& _text, ETextCommit::Type _commitMethod);

public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};
