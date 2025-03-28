#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MOPlayerController.generated.h"

class UMOChatInput;

/**
 * 
 */
UCLASS()
class ASSIGNMENT9_API AMOPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMOChatInput> ChatInputWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMOChatInput> ChatInputWidgetInstance;

protected:
	FString ChatMessageString;

public:
	void SetChatMessageString(const FString& _inChatMessageString);

	void PrintChatMessageString(const FString& _inChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& _inChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& _inChatMessageString);

public:
	virtual void BeginPlay() override;
};
