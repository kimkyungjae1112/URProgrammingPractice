// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CSAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API UCSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCSAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsJump : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovingThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float JumpingThreshould;
};
