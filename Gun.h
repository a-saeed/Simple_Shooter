// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLE_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	//function to pull the trigger, is public because it will be called from within the shooter character class
	void pullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	/*gun main components*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* root;

	UPROPERTY(VisibleAnywhere) //we make it "VisibleAnywhere" because they are pointers. we don't want to edit the pointers, just see them.
		USkeletalMeshComponent* gunMeshComponent; //we used skeletal mesh because the gun mesh in the asset pack is skeletal not static

	/*gun particle effects*/
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* particleMuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* particleBulletImpact;

	/*gun private variables*/
	UPROPERTY(EditAnywhere, Category = "Combat")
		float maxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float damageAmount = 15;

	/*gun private functions*/

	//perform the line trace
	bool gunTrace(FHitResult &outHit, FVector shotDirection);

	//get the owner controller
	AController* getOwnerController();
};
