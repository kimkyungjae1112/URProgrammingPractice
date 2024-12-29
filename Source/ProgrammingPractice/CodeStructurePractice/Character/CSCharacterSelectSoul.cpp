// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterSelectSoul.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACSCharacterSelectSoul::ACSCharacterSelectSoul()
{
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Soul"));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	StaticMeshComp = CREATE_COMP(UStaticMeshComponent, Static Mesh Component);
	StaticMeshComp->SetupAttachment(RootComponent);
	StaticMeshComp->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (StaticMeshRef.Object)
	{
		StaticMeshComp->SetStaticMesh(StaticMeshRef.Object);
	}

	SpringArmComp = CREATE_COMP(USpringArmComponent, SpringArm Component);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CREATE_COMP(UCameraComponent, Camera Component);
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Ref(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/Soul/IMC_Soul.IMC_Soul'"));
	if (IMC_Ref.Object)
	{
		IMC = IMC_Ref.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Soul/IMC_SoulMove.IMC_SoulMove'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Soul/IMC_SoulLook.IMC_SoulLook'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}
}

void ACSCharacterSelectSoul::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}
}

void ACSCharacterSelectSoul::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACSCharacterSelectSoul::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACSCharacterSelectSoul::Look);
}

APlayerController* ACSCharacterSelectSoul::GetMyController()
{
	return Cast<APlayerController>(GetController());
}

void ACSCharacterSelectSoul::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardDirection = CameraComp->GetForwardVector();
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputValue.X);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ACSCharacterSelectSoul::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

