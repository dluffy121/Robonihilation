// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class ROBONIHILATION_API AGun : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
		FName MuzzleFlashSocketName;

	UPROPERTY(EditAnywhere)
		float MaxBulletRange = 1000;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* MuzzleFlashParticles;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* BulletHitWorldParticles;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* BulletHitCharacterParticles;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* MuzzelSound;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* BulletHitSound;

	UPROPERTY(EditDefaultsOnly)
		float BulletHitSoundDelayPerUnit = 0.01f;

	UPROPERTY(EditDefaultsOnly)
		float Damage = 10;

public:
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool GunTrace(FHitResult& hitResult, FVector& shotDirection) const;

	AController* GetOwnerController() const;

	void PlayBulletHitSound(FVector location) const;
};
