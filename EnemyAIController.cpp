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
		
		APawn* enemyPawn = GetPawn();

		//setting the enemy character location as a blackboard key
		GetBlackboardComponent()->SetValueAsVector(TEXT("startLocation"), enemyPawn->GetActorLocation());
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
