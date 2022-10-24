// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "AIController.h"

void AKillEmAllGameMode::pawnKilled(APawn* killedPawn)
{
	Super::pawnKilled(killedPawn);

	//we need to cast the whichever custom player controller is set in the current game mode blueprint to APlayerController
	//because any new player controller we create will be derived from the APlayerController class
	//we need to get hold of the player controller to call the GameHasEnded() function
	//we will override GaneHasEnded() in our own custom player controller class to implement our own logic
	APlayerController* playerController = Cast <APlayerController>(killedPawn->GetController());

	//check if the player loses
	//if the pawn that is killed is actually the player character.. otherwise the cast would fail because player controller doesn't poesess ai characters
	if (playerController != nullptr)
	{
		playerController->GameHasEnded(nullptr, false);
	}
}
