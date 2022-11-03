// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"
#include <Blueprint/UserWidget.h>
#include <UMG/Public/Components/TextBlock.h>

void AShooterController::BeginPlay()
{
    ShowHUD();
}

void AShooterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HideHUD();
    ShowGameEndScreen(bIsWinner);

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterController::ShowGameEndScreen(bool bIsWinner)
{
    UUserWidget* gameEndScreen = CreateWidget(this, GameEndScreenClass, TEXT("Win Screen UI"));

    if (!gameEndScreen) return;

    UTextBlock* mainText = Cast<UTextBlock>(gameEndScreen->GetWidgetFromName(TEXT("MainText")));
    UTextBlock* secondaryText = Cast<UTextBlock>(gameEndScreen->GetWidgetFromName(TEXT("SecondaryText")));

    if (bIsWinner)
    {
        if (mainText)
        {
            mainText->SetText(WinMainText);
            mainText->SetColorAndOpacity(WinColor);
        }
        if (secondaryText)
        {
            secondaryText->SetText(WinSecondaryText);
            secondaryText->SetColorAndOpacity(WinColor);
        }
    }
    else
    {
        if (mainText)
        {
            mainText->SetText(LossMainText);
            mainText->SetColorAndOpacity(LossColor);
        }
        if (secondaryText)
        {
            secondaryText->SetText(LossSecondaryText);
            secondaryText->SetColorAndOpacity(LossColor);
        }
    }

    gameEndScreen->AddToViewport();
}

void AShooterController::ShowHUD()
{
    HUD = CreateWidget(this, HUDClass, TEXT("HUD"));

    if (!HUD) return;

    HUD->AddToViewport();
}

void AShooterController::HideHUD()
{
    if (!HUD) return;

    HUD->RemoveFromViewport();
}
