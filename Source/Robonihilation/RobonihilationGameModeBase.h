// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RobonihilationGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class ROBONIHILATION_API ARobonihilationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* killedPawn);
};
