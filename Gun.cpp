// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1- create the root component and set it as the default root
	root = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));
	SetRootComponent(root); //equivalent to RootComponent = root
	// 2- create the skeletal mesh component and attach it to the root
	gunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunComponent"));
	gunMeshComponent->SetupAttachment(root);
}

void AGun::pullTrigger()
{
	//spawn the muzzle flash particle effect at the attached socket of the gun's skeletal mesh, the muzzle (it should be a skeletal mesh to do this trick)
	if (particleMuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(particleMuzzleFlash, gunMeshComponent, TEXT("MuzzleFlashSocket"));
	}
	
	//we need to get the view point of the player, why?
	//to be able to make a line trace that simulates the bullet projection end point
	//the function to get it is located in a controller class
	//controllers are only meant for pawns that can be posessed (not guns!)
	//getOwner() gets the shooter character which owns this gun.. we alreday set the owner in the shooter character class
	//from there we can get the controller which controls the shooter character

	APawn* ownerPawn = Cast<APawn> (GetOwner());
	if (ownerPawn == nullptr) return;

	AController* ownerController = ownerPawn->GetController();
	if (ownerController == nullptr) return;

	FVector outLocation; //location of the view point of the camera, will be populated with the playerViewPoint() function.
	FRotator outRotation; //rotation of the view point of the camera, will be populated with the playerViewPoint() function.
	ownerController->GetPlayerViewPoint(outLocation, outRotation);
	
	//to do a line trace we need a start and end vector, we already have the start (outLocation)
	//end = start location + the direction in which the camera is pointing at * maxrange we want the bullet to travel..
	//the vector we get from that rotation will be of size 1
	FVector end = outLocation + outRotation.Vector() * maxRange;

	FHitResult outHit;
	bool hasHit = GetWorld()->LineTraceSingleByChannel(outHit, outLocation, end, ECollisionChannel::ECC_GameTraceChannel1); //create a channel "Bullet", can be found in config/DefaultEngine.

	if (hasHit)
	{
		//DrawDebugPoint(GetWorld(), outHit.Location, 20, FColor::Red, true); //outHit.ImpactPoint would work as well
		if (particleBulletImpact)
		{
			FVector shotDirection = -outRotation.Vector();//we need the impact particle effect to spawn with a rotation that is opposite to the direction of shooting. otherwise the effect could play inside of a wall or through a character.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleBulletImpact, outHit.Location, shotDirection.Rotation());
		}
		
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

