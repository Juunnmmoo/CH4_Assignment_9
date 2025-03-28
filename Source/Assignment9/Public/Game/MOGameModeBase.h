// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MOGameModeBase.generated.h"

class AMOPlayerController;
/**
 * 
 */
UCLASS()
class ASSIGNMENT9_API AMOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AMOPlayerController>> AllPlayerControllers;
	
public:
	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	void PrintChatMessageString(AMOPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	void IncreaseGuessCount(AMOPlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(AMOPlayerController* InChattingPlayerController, int InStrikeCount);


public:
	virtual void BeginPlay() override;

	virtual void OnPostLogin(AController* NewPlayer) override;
};
