// Fill out your copyright notice in the Description page of Project Settings.

#include "BlinkingCharacter.h"


// Sets default values
void ABlinkingCharacter::RightRotation()
{
	if (!MyTimeLine.IsPlaying() && (CurrentLine < 3))
	{
		CurrentLine++;
		if (BlickParticleBegin)
		{
			
			UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), BlickParticleBegin, this->GetTransform());
			
		}
		RotationSide = 1;
		bRightSide = true;
		InitialLocation = RootComponent->GetComponentLocation();
		MoveVector = InitialLocation + BlickToSide;
		FTimerHandle TimerH;
		GetWorldTimerManager().SetTimer(TimerH, this, &ABlinkingCharacter::CallEndsBlink, MyTimeLine.GetTimelineLength(), false);
		MyTimeLine.PlayFromStart();
	}
}

void ABlinkingCharacter::LeftRotation()
{
	if (!MyTimeLine.IsPlaying() && (CurrentLine > 1))
	{
		CurrentLine--;
		if (BlickParticleBegin)
		{
			
			UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), BlickParticleBegin, this->GetTransform());
			
			
		}
		bLeftSide = true;
		RotationSide = -1;
		InitialLocation = RootComponent->GetComponentLocation();
		MoveVector = InitialLocation - BlickToSide;
		
		FTimerHandle TimerH;
		GetWorldTimerManager().SetTimer(TimerH, this, &ABlinkingCharacter::CallEndsBlink, MyTimeLine.GetTimelineLength(), false);
		MyTimeLine.PlayFromStart();
	}
}

void ABlinkingCharacter::ControlRotation(float Value)
{
	// find out which way is right
	InitialLocation = RootComponent->GetComponentLocation();
	//MoveVector = InitialLocation + RotationSide*BlickToSide;
	FVector LocalNewPosition = FVector(InitialLocation.X,FMath::Lerp(InitialLocation.Y, MoveVector.Y, Value),InitialLocation.Z);
	RootComponent->SetWorldLocation(LocalNewPosition);
	/*
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value * RotationSide);
	*/
}

void ABlinkingCharacter::CallEndsBlink()
{
	if (BlickParticleEnd)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), BlickParticleEnd, this->GetTransform());
	}
	bRightSide = false;
	bLeftSide = false;
}

// Sets default values
ABlinkingCharacter::ABlinkingCharacter()
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

void ABlinkingCharacter::Death()
{
	DisableInput(UGameplayStatics::GetPlayerController(this, 0));

	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), DeathParticle, this->GetTransform());
	}

	Destroy();
}

// Called when the game starts or when spawned
void ABlinkingCharacter::BeginPlay()
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
void ABlinkingCharacter::Tick(float DeltaTime)
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
void ABlinkingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RightRotate", IE_Pressed, this, &ABlinkingCharacter::RightRotation);
	PlayerInputComponent->BindAction("LeftRotate", IE_Pressed, this, &ABlinkingCharacter::LeftRotation);

}

