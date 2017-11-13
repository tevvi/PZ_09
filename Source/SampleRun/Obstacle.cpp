// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacle.h"


// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMeshComponent"));

	ObstacleMeshComp->OnComponentHit.AddDynamic(this, &AObstacle::MyOnHit);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::MyOnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ARunnerCharacter* ThisChar = Cast<ARunnerCharacter>(OtherActor);
	if (ThisChar)
		ThisChar->Death();
	else
	{
		ABlinkingCharacter* ThisBlink = Cast<ABlinkingCharacter>(OtherActor);

		if (ThisBlink)
			ThisBlink->Death();
	}
}
