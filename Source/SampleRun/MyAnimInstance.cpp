// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningPawn = Cast<ABlinkingCharacter>(TryGetPawnOwner());
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!OwningPawn)
		return;


	UPawnMovementComponent* MovComponent = OwningPawn->FindComponentByClass<UPawnMovementComponent>();

	if (MovComponent)
	{
		IsInAir = MovComponent->IsFalling();
	}

	bLeft = OwningPawn->bLeftSide;
	bRight = OwningPawn->bRightSide;
	FVector V = OwningPawn->GetVelocity();

	Speed = V.Size();


}


