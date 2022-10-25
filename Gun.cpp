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
	if (particleMuzzleFlash && muzzleSound)
	{
		UGameplayStatics::SpawnEmitterAttached(particleMuzzleFlash, gunMeshComponent, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(muzzleSound, gunMeshComponent, TEXT("MuzzleFlashSocket"));
	}
	
	FHitResult outHit;
	FVector shotDirection;
	bool hasHit = gunTrace(outHit, shotDirection);

	if (hasHit)
	{
		//DrawDebugPoint(GetWorld(), outHit.Location, 20, FColor::Red, true); //outHit.ImpactPoint would work as well
		

		/*Apply damage to actors hit by the gun*/
		//we need to specify the damage event, which will be a point damage since we're using a gun.
		//then call Actor.TakeDamage() function
		AActor* hitActor = outHit.GetActor();	

		if (hitActor != nullptr) //if there's an actor that has been hit.
		{
			FPointDamageEvent damageEvent(damageAmount, outHit, shotDirection, nullptr);
			AController* ownerController = getOwnerController();
			hitActor->TakeDamage(damageAmount, damageEvent, ownerController, this);

			//play particle and sound effects
			if (particleBulletImpact && concreteImpactSound && playerImpactSound)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleBulletImpact, outHit.Location, shotDirection.Rotation());

				if (hitActor->ActorHasTag("character")) //if the actor hit is a character 
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), playerImpactSound, outHit.Location);
				}
				else
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), concreteImpactSound, outHit.Location);
				}
				
			}
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

bool AGun::gunTrace(FHitResult& outHit, FVector shotDirection)
{
	//we need to get the view point of the player, why?
	//to be able to make a line trace that simulates the bullet projection end point
	//the function to get it is located in a controller class
	//controllers are only meant for pawns that can be posessed (not guns!)
	//getOwner() gets the shooter character which owns this gun.. we alreday set the owner in the shooter character class
	//from there we can get the controller which controls the shooter character

	AController* ownerController = getOwnerController();

	if (ownerController == nullptr)
	{
		return false;
	}

	FVector outLocation; //location of the view point of the camera, will be populated with the playerViewPoint() function.
	FRotator outRotation; //rotation of the view point of the camera, will be populated with the playerViewPoint() function.

	ownerController->GetPlayerViewPoint(outLocation, outRotation);

	shotDirection = -outRotation.Vector();//we need the impact particle effect to spawn with a rotation that is opposite to the direction of shooting. otherwise the effect could play inside of a wall or through a character.

	//to do a line trace we need a start and end vector, we already have the start (outLocation)
	//end = start location + the direction in which the camera is pointing at * maxrange we want the bullet to travel..
	//the vector we get from that rotation will be of size 1
	FVector end = outLocation + outRotation.Vector() * maxRange;

	//query params that will be fed to the line trace function
	FCollisionQueryParams params;
	params.AddIgnoredActor(this); //don't hit the gun ur shooting with
	params.AddIgnoredActor(GetOwner()); //ignore yourself;

	return GetWorld()->LineTraceSingleByChannel(outHit, outLocation, end, ECollisionChannel::ECC_GameTraceChannel1, params); //create a channel "Bullet", can be found in config/DefaultEngine.

}

AController* AGun::getOwnerController()
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr) return nullptr;

	return ownerPawn->GetController();
}