// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isDead() const;

private:
	//Enemey ai controller private variables
	UPROPERTY(EditAnywhere)
	UBehaviorTree* behaviorAI;
	
	
};
