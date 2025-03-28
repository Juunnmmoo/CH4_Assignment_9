#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MOPlayerState.generated.h"

UCLASS()
class ASSIGNMENT9_API AMOPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;

public:
	FString GetPlayerInfoString();

public:
	AMOPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
