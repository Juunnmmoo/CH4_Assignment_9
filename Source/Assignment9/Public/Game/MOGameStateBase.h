// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MOGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT9_API AMOGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));
};
