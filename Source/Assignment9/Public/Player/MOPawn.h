#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MOPawn.generated.h"

UCLASS()
class ASSIGNMENT9_API AMOPawn : public APawn
{
	GENERATED_BODY()

public:
	AMOPawn();

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

};
