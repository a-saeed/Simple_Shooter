// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();	
	if (behaviorAI)
	{
		RunBehaviorTree(behaviorAI);
		
		//get pawns for the player, and the enemy (any character controlled by this ai controller)
		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		APawn* enemyPawn = GetPawn();

		//setting the player/enemy character location as a blackboard key
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("startLocation"), enemyPawn->GetActorLocation());
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//get the playable character
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//if the player pawn is in the enemy ai line of sight
	if (LineOfSightTo(playerPawn))
	{
		//update the player location and player last known location
		GetBlackboardComponent()->SetValueAsVector(TEXT("playerLocation"), playerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("playerLastKnownLocation"), playerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("playerLocation"));
	}
}
