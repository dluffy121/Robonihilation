// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include <EngineUtils.h>
#include <GameFramework/Controller.h>
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* killedPawn)
{
    Super::PawnKilled(killedPawn);

    APlayerController* playerController = Cast<APlayerController>(killedPawn->GetController());
    if (playerController)
        EndGame(false);

    for (AShooterAIController* shooterAIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!shooterAIController->IsDead())
            return;
    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool isPlayerWinner)
{
    for (AController* controller : TActorRange<AController>(GetWorld()))
    {
        // true == true => Player is winner
        // false == true => AI is not winner
        // true == false => Player is not winner
        // false == false => AI is winner
        bool isWinner = controller->IsPlayerController() == isPlayerWinner;
        controller->GameHasEnded(controller->GetPawn(), isWinner);
    }
}
