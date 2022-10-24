// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::pawnKilled(APawn* killedPawn)
{
	Super::pawnKilled(killedPawn);

	UE_LOG(LogTemp, Warning, TEXT("Kill Them AAll GameMode"));
}
