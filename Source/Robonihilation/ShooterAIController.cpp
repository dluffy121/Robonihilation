// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    TargetPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehavior)
        RunBehaviorTree(AIBehavior);

    Init_BBVariables_Patrol();
}

void AShooterAIController::Init_BBVariables_Patrol()
{
    auto blackboardComponent = GetBlackboardComponent();

    FVector pawnLocation = GetPawn()->GetActorLocation();
    blackboardComponent->SetValueAsVector(BT_Var_PatrolStartLocation, pawnLocation);
    pawnLocation += GetPawn()->GetActorForwardVector() * 1000;
    blackboardComponent->SetValueAsVector(BT_Var_PatrolEndLocation, pawnLocation);
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead()
{
    AShooterCharacter* controller = Cast<AShooterCharacter>(GetPawn());

    if (!controller) return true;    // Since controller does not exist it is assumed that pawn is dead

    return controller->IsDead();
}