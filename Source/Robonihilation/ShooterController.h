// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterController.generated.h"

/**
 *
 */
UCLASS()
class ROBONIHILATION_API AShooterController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float RestartDelay = 5.f;
	FTimerHandle RestartTimer;

#pragma region UI
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> GameEndScreenClass;

	UPROPERTY(EditDefaultsOnly)
		FText WinMainText = FText::FromString(TEXT("You Win!"));
	UPROPERTY(EditDefaultsOnly)
		FText WinSecondaryText = FText::FromString(TEXT("Restarting..."));
	UPROPERTY(EditDefaultsOnly)
		FSlateColor WinColor;

	UPROPERTY(EditDefaultsOnly)
		FText LossMainText = FText::FromString(TEXT("You Died!"));
	UPROPERTY(EditDefaultsOnly)
		FText LossSecondaryText = FText::FromString(TEXT("Restarting..."));
	UPROPERTY(EditDefaultsOnly)
		FSlateColor LossColor;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> HUDClass;
	UUserWidget* HUD;
#pragma endregion UI

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ShowGameEndScreen(bool bIsWinner);
	void ShowHUD();
	void HideHUD();
};
