// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Alert.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTService_Alert::UBTService_Alert()
{
    NodeName = "Update Character Alert State";
}

void UBTService_Alert::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!playerPawn) return;

    auto aiOwner = OwnerComp.GetAIOwner();
    if (!aiOwner) return;

    auto ownerPawn = aiOwner->GetPawn();

    bool alertValue = ownerPawn && ownerPawn != playerPawn && aiOwner->LineOfSightTo(playerPawn);

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), alertValue);
}
