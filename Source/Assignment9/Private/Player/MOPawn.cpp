#include "Player/MOPawn.h"
#include "Assignment9/Assignment9.h"

AMOPawn::AMOPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMOPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetModeString = Assignment9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *Assignment9FunctionLibrary::GetNetModeString(this), *NetModeString);
	Assignment9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void AMOPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetModeString = Assignment9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *Assignment9FunctionLibrary::GetNetModeString(this), *NetModeString);
	Assignment9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}



