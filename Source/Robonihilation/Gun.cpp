// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& hitResult, FVector& shotDirection) const
{
	AController* ownerController = GetOwnerController();
	if (!ownerController)
		return false;

	FVector location;
	FRotator rotation;

	shotDirection = -rotation.Vector();

	ownerController->GetPlayerViewPoint(location, rotation);

	FVector bulletEndLocation = location + rotation.Vector() * MaxBulletRange;

	FCollisionQueryParams colParams;
	colParams.AddIgnoredActor(this);
	colParams.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(hitResult, location, bulletEndLocation, ECollisionChannel::ECC_GameTraceChannel1, colParams);
}

AController* AGun::GetOwnerController() const
{
	APawn* owner = Cast<APawn>(GetOwner());
	if (!owner) return nullptr;

	return owner->GetController();
}

void AGun::PlayBulletHitSound(FVector location) const
{
	UGameplayStatics::PlaySoundAtLocation(this, BulletHitSound, location);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticles, Mesh, MuzzleFlashSocketName);
	UGameplayStatics::SpawnSoundAttached(MuzzelSound, Mesh, MuzzleFlashSocketName);

	FHitResult hitResult;
	FVector shotDirection;

	if (GunTrace(hitResult, shotDirection))
	{
		AActor* actor = hitResult.GetActor();

		if (!actor) return;

		if (actor->ActorHasTag("World"))
			UGameplayStatics::SpawnEmitterAtLocation(this, BulletHitWorldParticles, hitResult.ImpactPoint, shotDirection.Rotation(), true);

		if (actor->ActorHasTag("Character"))
			UGameplayStatics::SpawnEmitterAtLocation(this, BulletHitCharacterParticles, hitResult.ImpactPoint, shotDirection.Rotation(), true);

		FTimerHandle bulletHitDelayTH;
		FTimerDelegate playBulletHitSoundDel = FTimerDelegate::CreateUObject(
			this,
			&AGun::PlayBulletHitSound,
			FVector(hitResult.ImpactPoint)
		);

		GetWorldTimerManager().SetTimer(
			bulletHitDelayTH,
			playBulletHitSoundDel,
			BulletHitSoundDelayPerUnit * hitResult.Distance,
			false
		);

		FPointDamageEvent DamageEvent(Damage, hitResult, shotDirection, nullptr);
		actor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
	}
}