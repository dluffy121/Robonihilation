// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include "Gun.h"
#include "RobonihilationGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("R Shoulder Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("R Shoulder Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(GunBoneName, EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GunSocketName);
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Walk);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &AShooterCharacter::StopWalk);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float damageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	damageToApply = FMath::Min(Health, damageToApply);
	Health -= damageToApply;

	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		ARobonihilationGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ARobonihilationGameModeBase>();
		if (gameMode)
			gameMode->PawnKilled(this);

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return damageToApply;
}

void AShooterCharacter::MoveForward(float value)
{
	value *= GetWalkReduction();
	AddMovementInput(GetActorForwardVector() * value);
}

void AShooterCharacter::MoveRight(float value)
{
	value *= GetWalkReduction();
	AddMovementInput(GetActorRightVector() * value);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

void AShooterCharacter::Walk()
{
	IsWalking = true;
}

void AShooterCharacter::StopWalk()
{
	IsWalking = false;
}

void AShooterCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AShooterCharacter::LookRight(float value)
{
	AddControllerYawInput(value);
}

void AShooterCharacter::LookUpRate(float value)
{
	AddControllerPitchInput(value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float value)
{
	AddControllerYawInput(value * RotationRate * GetWorld()->GetDeltaSeconds());
}

float AShooterCharacter::GetWalkReduction()
{
	float lerpPercent;

	if (IsWalking)
	{
		CurrentWalkLerpTime += GetWorld()->GetDeltaSeconds();
		CurrentWalkLerpTime = FMath::Clamp(CurrentWalkLerpTime, 0.0f, EnterWalkLerpTime);
		lerpPercent = CurrentWalkLerpTime / EnterWalkLerpTime;
	}
	else
	{
		CurrentWalkLerpTime -= GetWorld()->GetDeltaSeconds();
		CurrentWalkLerpTime = FMath::Clamp(CurrentWalkLerpTime, 0.0f, ExitWalkLerpTime);
		lerpPercent = CurrentWalkLerpTime / ExitWalkLerpTime;
	}

	return 1 - (lerpPercent * WalkMoveSpeedReduction);
}