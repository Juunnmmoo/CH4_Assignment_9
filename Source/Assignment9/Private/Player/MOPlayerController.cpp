#include "Player/MOPlayerController.h"
#include "Assignment9/Assignment9.h"
#include "Game/MOGameModeBase.h"
#include "Player/MOPlayerState.h"
#include "UI/MOChatInput.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"

void AMOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsLocalController() == false)
		return;


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

	//PrintChatMessageString(ChatMessageString);
	
	if (IsLocalController() == true)
	{
		//ServerRPCPrintChatMessageString(_inChatMessageString);

		AMOPlayerState* MOPlayerState = GetPlayerState<AMOPlayerState>();
		if (IsValid(MOPlayerState) == true)
		{
			//FString CombineMessageString = MOPlayerState->PlayerNameString + TEXT(": ") + _inChatMessageString;
			FString CombineMessageString = MOPlayerState->GetPlayerInfoString() + TEXT(": ") + _inChatMessageString;
			ServerRPCPrintChatMessageString(CombineMessageString);
		}
	}

}

void AMOPlayerController::PrintChatMessageString(const FString& _inChatMessageString)
{
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);

	//FString NetModeString = Assignment9FunctionLibrary::GetNetModeString(this);
	//FString CombineMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *_inChatMessageString);
	//Assignment9FunctionLibrary::MyPrintString(this, CombineMessageString, 10.f);

	Assignment9FunctionLibrary::MyPrintString(this, _inChatMessageString, 10.f);
}

void AMOPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& _inChatMessageString)
{
	PrintChatMessageString(_inChatMessageString);

}

void AMOPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& _inChatMessageString)
{
	//for (TActorIterator<AMOPlayerController> It(GetWorld()); It; ++It)
	//{
	//	AMOPlayerController* MOPlayerController = *It;
	//
	//	if (IsValid(MOPlayerController) == true)
	//	{
	//		MOPlayerController->ClientRPCPrintChatMessageString(_inChatMessageString);
	//	}
	//}

	AGameModeBase* GMB = UGameplayStatics::GetGameMode(this);
	if (IsValid(GMB) == true)
	{
		AMOGameModeBase* MOGMB = Cast<AMOGameModeBase>(GMB);
		if (IsValid(MOGMB) == true)
		{
			MOGMB->PrintChatMessageString(this, _inChatMessageString);
		}
	}
}
