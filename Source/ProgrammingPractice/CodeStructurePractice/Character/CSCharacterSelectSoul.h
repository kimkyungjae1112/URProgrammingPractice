// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CSCharacterSelectSoul.generated.h"

#define CREATE_COMP(KlassName, CompName) CreateDefaultSubobject<KlassName>(TEXT(#CompName))

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USphereComponent;

UCLASS()
class PROGRAMMINGPRACTICE_API ACSCharacterSelectSoul : public ACharacter
{
	GENERATED_BODY()

public:
	ACSCharacterSelectSoul();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	APlayerController* GetMyController();

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
