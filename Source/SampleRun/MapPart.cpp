// Fill out your copyright notice in the Description page of Project Settings.

#include "MapPart.h"


// Sets default values
AMapPart::AMapPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	RootComponent = SpawnPoint;

	NextPathPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("NextPathPoint"));
	NextPathPoint->SetupAttachment(RootComponent);

	EndsCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EndsCollision"));
	EndsCollision->SetupAttachment(RootComponent);

	TimeToNextSpawn = 0.5f;

	EndsCollision->OnComponentBeginOverlap.AddDynamic(this, &AMapPart::DoDestroySelf);

	ClassToSpawn = this->StaticClass();
}

void AMapPart::NextSpawn()
{
	auto thisworld = GetWorld();
	if (thisworld)
	{
		auto SpawnLocation = NextPathPoint->GetComponentTransform();
		thisworld->SpawnActor(ClassToSpawn, &SpawnLocation);
	}
}

void AMapPart::DoDestroySelf(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ARunnerCharacter>(OtherActor))
	{
		FTimerHandle TimerH;
		GetWorldTimerManager().SetTimer(TimerH, this, &AMapPart::CallDestroy, 2.f, false);
	}
}

void AMapPart::CallDestroy()
{
	for (auto& i : Obstacles)
	{
		i->Destroy();
		//i = nullptr;
		//Obstacles.Remove(i);
	}
	Destroy();
}
// Called when the game starts or when spawned
void AMapPart::BeginPlay()
{
	Super::BeginPlay();

	if (ObstacleClass)
	{
		int32 obstacleL = FMath::RandRange(0, ObstaclesPoints.Num() - 1);
		auto SpawnTransform = ObstaclesPoints[obstacleL]->GetComponentTransform();
		auto SpawnedObs = GetWorld()->SpawnActor(ObstacleClass, &SpawnTransform);
		SpawnedObs->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
		Obstacles.Add(SpawnedObs);
	}

	FTimerHandle TimerH;
	GetWorldTimerManager().SetTimer(TimerH, this, &AMapPart::NextSpawn, TimeToNextSpawn, false);
}

// Called every frame
void AMapPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

