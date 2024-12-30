// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACSCharacterBase::ACSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	BoxComp = CREATE_COMP(UBoxComponent, Box Component);
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACSCharacterBase::SelectedBySoulOnOverlap);
	
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SpringArmComp = CREATE_COMP(USpringArmComponent, SpringArm Component);
	SpringArmComp->SetupAttachment(GetMesh());

	CameraComp = CREATE_COMP(UCameraComponent, Camera Component);
	CameraComp->SetupAttachment(SpringArmComp);
}

void ACSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UClass* ACSCharacterBase::SelectedBySoul()
{
	return StaticClass();
}

void ACSCharacterBase::SelectedBySoulOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Display, TEXT("Super :: 닿았냐?"));
		OnSignChangePlayer.ExecuteIfBound();
	}
}

void ACSCharacterBase::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void ACSCharacterBase::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

