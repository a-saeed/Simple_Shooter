// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Simple_ShooterGameModeBase.h"

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
	
	//set health equal to max health
	health = maxHealth;

	//at begin play.. spawn the gun actor
	gun = GetWorld()->SpawnActor<AGun>(gunClass);

	//hide the original gun attached to the character asset by hiding the bone attached to it
	//GetMesh() is the mesh of the shooter character (this class)
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// we need to attach our "runtime-spawned gun" to the this shooter character's mesh component (at runtime)
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));

	//set the owner of this spawned gun to the shooter character (needed in applying damage AND multiplayers)
	gun->SetOwner(this);

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

	//bind the shoot function
	PlayerInputComponent->BindAction(TEXT("shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//what if damage to apply is greater than health
	damageToApply = FMath::Min(health, damageToApply);

	health -= damageToApply;

	if (isDead())
	{
		//get hold of the game mode
		ASimple_ShooterGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ASimple_ShooterGameModeBase>();
		if (gameMode != nullptr)
		{
			gameMode->pawnKilled(this);
		}

		DetachFromControllerPendingDestroy(); //disable the controller once the character is dead
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //disable the capsule component on the character

	}
	return damageToApply; //the amount of damage done.. zero if health is depleted
}

bool AShooterCharacter::isDead() const
{
	return health <= 0;
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

float AShooterCharacter::getHealthPercentage() const
{
	return health / maxHealth;
}

void AShooterCharacter::shoot()
{
	gun->pullTrigger();
}



