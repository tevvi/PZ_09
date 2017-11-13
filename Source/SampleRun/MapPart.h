// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Obstacle.h"
#include "RunnerCharacter.h"
#include "MapPart.generated.h"

UCLASS()
class SAMPLERUN_API AMapPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapPart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* NextPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UArrowComponent*> ObstaclesPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* EndsCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AObstacle> ObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Obstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMapPart> ClassToSpawn;

	float TimeToNextSpawn;

	UFUNCTION(BlueprintCallable)
	void NextSpawn();

	UFUNCTION(BlueprintCallable)
	void CallDestroy();

	UFUNCTION(BlueprintCallable)
	void DoDestroySelf(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
