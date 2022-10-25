// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//setup a HUD screen
	hudScreen = CreateWidget(this, hudScreenClass);
	if (hudScreen != nullptr)
	{
		hudScreen->AddToViewport();
	}
	
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	//when game ends, remove the hud display from the viewport
	hudScreen->RemoveFromViewport();

	if (bIsWinner) //if the player wins
	{
		//setup a win screen
		UUserWidget* winScreen = CreateWidget(this, winScreenClass);

		if (winScreen != nullptr)
		{
			//add the widget to viewport
			winScreen->AddToViewport();
		}
	}
	else
	{
		//setup the lose screen widget in the player controller, because a controller can own a widget
		UUserWidget* loseScreen = CreateWidget(this, loseScreenClass);

		if (loseScreen != nullptr)
		{
			//add the widget to viewport
			loseScreen->AddToViewport();
		}
	}


	GetWorldTimerManager().SetTimer(restartHandle, this, &APlayerController::RestartLevel, restartDelay);
}
