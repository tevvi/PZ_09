// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BlinkingCharacter.generated.h"

UCLASS()
class SAMPLERUN_API ABlinkingCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	FTimeline MyTimeLine;

	UFUNCTION()
	void RightRotation();

	UFUNCTION()
	void LeftRotation();

	UFUNCTION()
	void ControlRotation(float Value);

	int RotationSide = 0;

	UFUNCTION()
	void CallEndsBlink();

	int CurrentLine = 2;

	FVector MoveVector;
	FVector InitialLocation;

public:


	bool bRightSide = false;
	bool bLeftSide = false;
	// Sets default values for this character's properties
	ABlinkingCharacter();

	UPROPERTY(EditAnywhere, Category = "Animation")
	UCurveFloat* AnimCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.3;

	UFUNCTION(BlueprintCallable)
	void Death();

	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BlickParticleBegin;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BlickParticleEnd;

	UPROPERTY(EditAnywhere)
	FVector BlinkForward;

	UPROPERTY(EditAnywhere)
	FVector BlickToSide;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
