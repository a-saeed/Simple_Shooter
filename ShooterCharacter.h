// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
UCLASS()
class SIMPLE_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/*functions to bind the input action mapping for the character*/
	void moveVertical(float inputValue);
	void moveHorizontal(float inputValue);
	void shoot(); //an intermediary function to help bind the pullTrigger() function in the Gun class...

	//variables to manipulate the gun class
	UPROPERTY()
		AGun* gun;						//this is the pointer that will hold wichever gun will be spawned (could be a rifle, sniper, etc...)
	UPROPERTY(EditDefaultsOnly, Category = "Combat")			//this will be set in blueprint to choose which type gun we want to spawn (needs to be a bluePrint based on the gun class)
		TSubclassOf<AGun> gunClass;

};
