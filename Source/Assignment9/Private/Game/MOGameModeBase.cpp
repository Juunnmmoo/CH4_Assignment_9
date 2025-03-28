// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MOGameModeBase.h"
#include "Game/MOGameStateBase.h"
#include "Player/MOPlayerController.h"
#include "Player/MOPlayerState.h"
#include "EngineUtils.h"


void AMOGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
}

void AMOGameModeBase::OnPostLogin(AController* NewPlayer)
{
	//Super::OnPostLogin(NewPlayer);
	//
	//AMOGameStateBase* MOGameStateBase = GetGameState<AMOGameStateBase>();
	//if (IsValid(MOGameStateBase) == true)
	//{
	//	MOGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXX"));
	//}
	//
	//AMOPlayerController* MOPlayerController = Cast<AMOPlayerController>(NewPlayer);
	//if (IsValid(MOPlayerController) == true)
	//{
	//	AllPlayerControllers.Add(MOPlayerController);
	//}

	AMOPlayerController* MOPlayerController = Cast<AMOPlayerController>(NewPlayer);
	if (IsValid(MOPlayerController) == true)
	{
		AllPlayerControllers.Add(MOPlayerController);

		AMOPlayerState* MOPlayerState = MOPlayerController->GetPlayerState<AMOPlayerState>();
		if (IsValid(MOPlayerState) == true)
		{
			MOPlayerState->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		AMOGameStateBase* MOGmameStateBase = GetGameState<AMOGameStateBase>();
		if (IsValid(MOGmameStateBase) == true)
		{
			MOGmameStateBase->MulticastRPCBroadcastLoginMessage(MOPlayerState->PlayerNameString);
		}
	}
}

FString AMOGameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; i++)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num) {return Num > 0;});

	FString Result;
	for (int32 i = 0; i < 3; i++)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

bool AMOGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do 
	{
		if (InNumberString.Len() != 3)
			break;
	
		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}
		
		if (bIsUnique == false)
			break;

		bCanPlay = true;
	} while (false);


	return bCanPlay;
}

FString AMOGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0; 
	int32 BallCount = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%C"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
		return TEXT("OUT");

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void AMOGameModeBase::PrintChatMessageString(AMOPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString ChatMessageString = InChatMessageString;
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		
		IncreaseGuessCount(InChattingPlayerController);

		for (TActorIterator<AMOPlayerController> It(GetWorld()); It; ++It)
		{
			AMOPlayerController* MOPlayerController = *It;
			if(IsValid(MOPlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				MOPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);

				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<AMOPlayerController> It(GetWorld()); It; ++It)
		{
			AMOPlayerController* MOPlayerController = *It;
			if (IsValid(MOPlayerController) == true)
			{
				MOPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}

}

void AMOGameModeBase::IncreaseGuessCount(AMOPlayerController* InChattingPlayerController)
{
	AMOPlayerState* MOPlayerState = InChattingPlayerController->GetPlayerState<AMOPlayerState>();
	if (IsValid(MOPlayerState) == true)
	{
		MOPlayerState->CurrentGuessCount++;
	}
}

void AMOGameModeBase::ResetGame()
{
}

void AMOGameModeBase::JudgeGame(AMOPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (InStrikeCount == 3)
	{
		AMOPlayerState* MOPlayerState = InChattingPlayerController->GetPlayerState<AMOPlayerState>();
		
		if (IsValid(MOPlayerState) == true)
		{
			FString CombinedMessageString = MOPlayerState->PlayerNameString + TEXT("has won the game.");
			for (const auto& MOPlayerController : AllPlayerControllers)
			{
				MOPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
		
		ResetGame();
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& MOPlayerController : AllPlayerControllers)
		{
			AMOPlayerState* MOPlayerState = InChattingPlayerController->GetPlayerState<AMOPlayerState>();
			if (IsValid(MOPlayerState) == true)
			{
				if (MOPlayerState->CurrentGuessCount <= MOPlayerState->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}
		if (true == bIsDraw)
		{
			for (const auto& MOPlayerController : AllPlayerControllers)
			{
				MOPlayerController->ClientRPCPrintChatMessageString(TEXT("Draw..."));

			}
			ResetGame();

		}

	}

}
