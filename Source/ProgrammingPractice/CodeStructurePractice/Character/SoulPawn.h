// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SoulPawn.generated.h"

#define CREATE_COMP(KlassName, CompName) CreateDefaultSubobject<KlassName>(TEXT(#CompName))

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USphereComponent;

UCLASS()
class PROGRAMMINGPRACTICE_API ASoulPawn : public APawn
{
	GENERATED_BODY()

public:
	ASoulPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	APlayerController* GetMyController();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
