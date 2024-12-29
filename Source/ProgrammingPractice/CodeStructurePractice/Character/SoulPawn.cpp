// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/SoulPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

ASoulPawn::ASoulPawn()
{
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	SphereComp = CREATE_COMP(USphereComponent, Sphere Component);
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName(TEXT("NoCollision"));

	StaticMeshComp = CREATE_COMP(UStaticMeshComponent, Static Mesh Component);
	StaticMeshComp->SetupAttachment(SphereComp);
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

void ASoulPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}
}

void ASoulPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulPawn::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulPawn::Look);
}

APlayerController* ASoulPawn::GetMyController()
{
	return CastChecked<APlayerController>(GetController());
}

void ASoulPawn::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FVector ForwardVector = GetActorForwardVector() * 100.f * InputValue.X * GetWorld()->GetDeltaSeconds();
	FVector RightVector = GetActorRightVector() * 100.f * InputValue.Y * GetWorld()->GetDeltaSeconds();

	AddActorLocalOffset(ForwardVector);
	AddActorLocalOffset(RightVector);
}

void ASoulPawn::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

