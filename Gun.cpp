// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"

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

