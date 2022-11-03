// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 *
 */
UCLASS()
class ROBONIHILATION_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

private:
	APawn* TargetPawn;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* AIBehavior;

	UPROPERTY(EditDefaultsOnly)
		FName BT_Var_PlayerLocation;
	UPROPERTY(EditDefaultsOnly)
		FName BT_Var_LastKnownPlayerLocation;
	UPROPERTY(EditDefaultsOnly)
		FName BT_Var_PatrolStartLocation;
	UPROPERTY(EditDefaultsOnly)
		FName BT_Var_PatrolEndLocation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsDead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Init_BBVariables_Patrol();
};
