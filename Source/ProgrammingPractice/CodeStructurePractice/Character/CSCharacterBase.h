// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CSCharacterBase.generated.h"

#define CREATE_COMP(KlassName, CompName) CreateDefaultSubobject<KlassName>(TEXT(#CompName))
DECLARE_DELEGATE(FOnSignChangePlayer)

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class APlayerController;

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

public:
	FOnSignChangePlayer OnSignChangePlayer;
	virtual UClass* GetCharacterClass();
	void RegisterInputSystem();

/* Utility */
protected:
	APlayerController* GetMyController();

/* Camera */
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

private:
	UFUNCTION()
	void SelectedBySoulOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

/* Input */
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void QuickSoul();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UInputAction> QuickSoulAction;
};
