// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CSCharacterBase.generated.h"

#define CREATE_COMP(KlassName, CompName) CreateDefaultSubobject<KlassName>(TEXT(#CompName))
DECLARE_DELEGATE_OneParam(FOnSignChangePlayer, UClass* /* Static Class */)

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class APlayerController;
class UCSDefaultAttackComponent;
class UCSInputDataAsset;

UENUM()
enum class EPlayerClass : uint8
{
	EWarrior,
	EWraith
};

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
	void RegisterInputSystem();

/* Utility */
protected:
	virtual UClass* GetCharacterClass();
	virtual EPlayerClass GetPlayerClassType();

	APlayerController* GetMyController();

/* Component */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UCSDefaultAttackComponent> DefaultAttackComp;

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
protected:
	virtual void DefaultAttack();
	virtual void Run();
	virtual void Jump();
	virtual void EquipWeapon();

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void QuickToSoul();

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<UCSInputDataAsset> InputData;
};
