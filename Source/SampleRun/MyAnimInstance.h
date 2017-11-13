// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BlinkingCharacter.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLERUN_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool bRight;

	ABlinkingCharacter* OwningPawn;

	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaTimeX)override;

};