// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobonihilationGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 *
 */
UCLASS()
class ROBONIHILATION_API AKillEmAllGameMode : public ARobonihilationGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* killedPawn) override;

private:
	void EndGame(bool isPlayerWinner);
};
