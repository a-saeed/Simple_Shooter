// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("update player location if seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//get the playable character
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (playerPawn == nullptr)
	{
		return;
	}

	//we need to check the line of sight of the enemy to see if the player is visible.
	AAIController* enemyController = OwnerComp.GetAIOwner();

	if (enemyController == nullptr)
	{
		return;
	}
	
	bool isPlayerInMyLineOfSight = enemyController->LineOfSightTo(playerPawn);

	if (isPlayerInMyLineOfSight)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerPawn->GetActorLocation());
	}
	else
	{
		//if hes's not, clear the player location from my memory.. all i have now is a last known location
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
