// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	//in a task constructor we always give it a name
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory); //this line is "Super" important  to not forget..
	
	//we need to get hold of the pawn (which is the ai shooter character)
	//to get hold of a pawn we need its controller which has a function to call get pawn
	//we know that OwnerComp is a UBehaviorTreeComponent that is attached to an ai character/controller.
	//when searching in UBehaviorTreeComponent we find nothing related to a getting controller
	//so we search within the parent of UBehaviorTreeComponent,, which is UBrainComponent

	AAIController* aiController = OwnerComp.GetAIOwner();
	
	if (aiController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* enemyCharacter = Cast<AShooterCharacter>(aiController->GetPawn());

	if (enemyCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//call the shoot function
	enemyCharacter->shoot();

	return EBTNodeResult::Succeeded;
}
