// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerCharacter.h"


void ARunnerCharacter::RightRotation()
{
	if (!MyTimeLine.IsPlaying())
	{
		RotationSide = 1;
		MyTimeLine.PlayFromStart();
	}
}

void ARunnerCharacter::LeftRotation()
{
	if (!MyTimeLine.IsPlaying())
	{
		RotationSide = -1;
		MyTimeLine.PlayFromStart();
	}
}

void ARunnerCharacter::ControlRotation(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);



	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value * RotationSide);
	/*
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value * RotationSide);
	*/
}

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 3000.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

}

void ARunnerCharacter::Death()
{
	DisableInput(UGameplayStatics::GetPlayerController(this, 0));

	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), DeathParticle, this->GetTransform());
	}

	Destroy();
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AnimCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("ControlRotation"));
		MyTimeLine.AddInterpFloat(AnimCurve, ProgressFunction);
		MyTimeLine.SetLooping(false);
	}
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeLine.TickTimeline(DeltaTime);
	if (Controller != NULL)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Speed);
	}
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RightRotate", IE_Pressed, this, &ARunnerCharacter::RightRotation);
	PlayerInputComponent->BindAction("LeftRotate", IE_Pressed, this, &ARunnerCharacter::LeftRotation);

}

