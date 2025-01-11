// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASPratice/Character/GCharacterBase.h"
#include "InputActionValue.h"
#include "GPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGInputDataAsset;

UCLASS()
class PROGRAMMINGPRACTICE_API AGPlayerCharacter : public AGCharacterBase
{
	GENERATED_BODY()

public:
	AGPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;

private:
	void InitAbilitySystemComponent();

/* Camera */
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

/* Input */
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UGInputDataAsset> InputData;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Test_Q();

};
