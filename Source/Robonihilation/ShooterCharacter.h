// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class ROBONIHILATION_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
		float RotationRate = 5.f;

	// Walking
	UPROPERTY(VisibleAnywhere)
		bool IsWalking = false;

	UPROPERTY(EditDefaultsOnly)
		float WalkMoveSpeedReduction = 0.125f;

	UPROPERTY(VisibleAnywhere)
		float CurrentWalkLerpTime;

	UPROPERTY(EditDefaultsOnly)
		float EnterWalkLerpTime = 0.3f;

	UPROPERTY(EditDefaultsOnly)
		float ExitWalkLerpTime = 0.3f;

	float CurrentExitWalkTime;

	// Combat
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY()
		AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
		FName GunBoneName;

	UPROPERTY(EditDefaultsOnly)
		FName GunSocketName;

	// Health
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health;

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
		inline bool IsDead() const { return Health <= 0; }

	UFUNCTION(BlueprintPure)
		inline float GetHealthPercent() const { return Health / MaxHealth; }

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Common Input
	void MoveForward(float value);
	void MoveRight(float value);

	// Keyboard Input
	void Walk();
	void StopWalk();

	// Mouse Input
	void LookUp(float value);
	void LookRight(float value);

	// Controller Input
	void LookUpRate(float value);
	void LookRightRate(float value);

	// Walking
	float GetWalkReduction();
};