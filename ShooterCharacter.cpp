// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind the input action mapping for the player.. 'this' mean we want to apply this move funtion pn this character object
	//looking up, right and jumping are already implemented in classes Pawn and Character..
	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &AShooterCharacter::moveVertical);
	PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &AShooterCharacter::moveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AShooterCharacter::moveVertical(float inputValue)
{
	//this function is inherited from the character class, no need to implement any movement logic of our own..
	//input is a valur between 1,-1.. if -ve, then we move backwards.
	AddMovementInput(GetActorForwardVector() * inputValue);
}

void AShooterCharacter::moveHorizontal(float inputValue)
{
	AddMovementInput(GetActorRightVector() * inputValue);
}



