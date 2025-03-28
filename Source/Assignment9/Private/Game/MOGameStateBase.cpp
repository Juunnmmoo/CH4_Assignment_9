#include "Game/MOGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MOPlayerController.h"

void AMOGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			AMOPlayerController* MOPlayerController = Cast<AMOPlayerController>(PC);
			if (IsValid(MOPlayerController) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				MOPlayerController->PrintChatMessageString(NotificationString);
			}
		}
	}
}
