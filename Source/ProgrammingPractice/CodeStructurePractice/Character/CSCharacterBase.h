// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CSCharacterBase.generated.h"

UCLASS()
class PROGRAMMINGPRACTICE_API ACSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACSCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


};
