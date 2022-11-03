// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!playerPawn) return;
    
    auto aiOwner = OwnerComp.GetAIOwner();
    if (!aiOwner) return;

    if (aiOwner->LineOfSightTo(playerPawn))
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), playerPawn);
    else
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}
