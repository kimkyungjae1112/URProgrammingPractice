// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Animation/CSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCSAnimInstance::UCSAnimInstance()
{
	MovingThreshould = 3.f;
	JumpingThreshould = 30.f;
}

void UCSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
		check(Movement);
	}
}

void UCSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		GroundSpeed = Movement->Velocity.Size();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJump = bIsFalling & (Movement->Velocity.Z > JumpingThreshould);
	}
}
