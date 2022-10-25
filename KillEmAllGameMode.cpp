// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "EnemyAIController.h"

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
		//end game, player didn't win
		endGame(false);
	}

	//if the killed pawn isn't a player character
	for (AEnemyAIController* enemyController : TActorRange<AEnemyAIController>(GetWorld()))
	{
		//for each enemy controller existing in the level now, return early if at least one enemy ai is still alive
		if (!enemyController->isDead())
		{
			return;
		}
	}
	endGame(true); //end the game siganling that the player has won
}

void AKillEmAllGameMode::endGame(bool bIsPlayerWinner)
{
	//iterate over all controllers in the world (including the AI)
	for (AController* controller : TActorRange<AController>(GetWorld()))
	{
		//check if its a player controller with a built-in function without casting
		//we end the game if player OR the ai wins
		//we resume the game if 
		bool bIsWinner = controller->IsPlayerController() == bIsPlayerWinner;
		controller->GameHasEnded(controller->GetPawn(), bIsWinner);
	}
}
