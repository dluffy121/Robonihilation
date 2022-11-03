// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* owner = OwnerComp.GetAIOwner();
    if (!owner) return EBTNodeResult::Failed;

    AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(owner->GetPawn());
    if (!shooterCharacter) return EBTNodeResult::Failed;

    shooterCharacter->Shoot();

    return EBTNodeResult::Succeeded;
}
