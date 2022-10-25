// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

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

bool AEnemyAIController::isDead() const
{
	//this function will be called in the game moood on each ai controller
	//we're basically delegating its functionality to the isDead() function in the shooter character class.. this is the most robust way
	AShooterCharacter* enemyCharacter = Cast<AShooterCharacter>(GetPawn());
	if (enemyCharacter != nullptr)
	{
		return enemyCharacter->isDead();
	}

	//if there isn't a controller, it means that there is no character
	return true; //character is as good as dead.
}
