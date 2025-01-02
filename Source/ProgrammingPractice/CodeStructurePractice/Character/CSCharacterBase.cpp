// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "CodeStructurePractice/Game/CodeStructureGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

ACSCharacterBase::ACSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACSCharacterBase::SelectedBySoulOnOverlap);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	SpringArmComp = CREATE_COMP(USpringArmComponent, SpringArm Component);
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CREATE_COMP(UCameraComponent, Camera Component);
	CameraComp->SetupAttachment(SpringArmComp);

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Ref(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/Character/IMC_Character.IMC_Character'"));
	if (IMC_Ref.Object)
	{
		IMC_Default = IMC_Ref.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Character/IMC_CharacterMove.IMC_CharacterMove'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Character/IMC_CharacterLook.IMC_CharacterLook'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Character/IMC_CharacterJump.IMC_CharacterJump'"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> QuickSoulActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Character/IMC_CharacterChange.IMC_CharacterChange'"));
	if (QuickSoulActionRef.Object)
	{
		QuickSoulAction = QuickSoulActionRef.Object;
	}

	
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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACSCharacterBase::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACSCharacterBase::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(QuickSoulAction, ETriggerEvent::Started, this, &ACSCharacterBase::QuickSoul);
}

UClass* ACSCharacterBase::GetCharacterClass()
{
	return StaticClass();
}

void ACSCharacterBase::RegisterInputSystem()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
}

void ACSCharacterBase::SelectedBySoulOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		OnSignChangePlayer.ExecuteIfBound();
	}
}

APlayerController* ACSCharacterBase::GetMyController()
{
	return CastChecked<APlayerController>(GetController());
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

void ACSCharacterBase::QuickSoul()
{
	ACodeStructureGameMode* GameMode = Cast<ACodeStructureGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->QuickSoulInPlayer();
	}
}

