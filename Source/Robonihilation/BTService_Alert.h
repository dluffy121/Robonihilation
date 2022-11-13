// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Alert.generated.h"

/**
 *
 */
UCLASS()
class ROBONIHILATION_API UBTService_Alert : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_Alert();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
