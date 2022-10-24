// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PLayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTService_PLayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_PLayerLocation();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
