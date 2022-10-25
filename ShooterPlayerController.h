// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	float restartDelay = 5.0f;

	FTimerHandle restartHandle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> loseScreenClass; //because we're calling a blueprint basically..

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> winScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> hudScreenClass;

	UPROPERTY()
		UUserWidget* hudScreen;
};
