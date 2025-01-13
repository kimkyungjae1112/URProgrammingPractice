// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "CodeStructurePractice/Game/CodeStructureGameMode.h"
#include "CodeStructurePractice/Component/CSDefaultAttackComponent.h"
#include "CodeStructurePractice/Data/CSInputDataAsset.h"
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
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CREATE_COMP(UCameraComponent, Camera Component);
	CameraComp->SetupAttachment(SpringArmComp);

	DefaultAttackComp = CREATE_COMP(UCSDefaultAttackComponent, Default Attack Comp);

	static ConstructorHelpers::FObjectFinder<UCSInputDataAsset> InputDataRef(TEXT("/Script/ProgrammingPractice.CSInputDataAsset'/Game/CS/Data/DA_Input.DA_Input'"));
	if (InputDataRef.Object)
	{
		InputData = InputDataRef.Object;
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

	EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &ACSCharacterBase::Move);
	EnhancedInputComponent->BindAction(InputData->LookAction, ETriggerEvent::Triggered, this, &ACSCharacterBase::Look);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(InputData->QuickSoulAction, ETriggerEvent::Started, this, &ACSCharacterBase::QuickToSoul);
	EnhancedInputComponent->BindAction(InputData->DefaultAttackAction, ETriggerEvent::Started, this, &ACSCharacterBase::DefaultAttack);
}

UClass* ACSCharacterBase::GetCharacterClass()
{
	return StaticClass();
}

EPlayerClass ACSCharacterBase::GetPlayerClassType()
{
	return EPlayerClass();
}

void ACSCharacterBase::RegisterInputSystem()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputData->IMC_Default, 0);
	}
}

void ACSCharacterBase::SelectedBySoulOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor)
	{
		OnSignChangePlayer.ExecuteIfBound(GetCharacterClass());
		if (GetPlayerClassType() == EPlayerClass::EWarrior)
		{
			DefaultAttackComp->LoadAssetAsync(EAssetType::Warrior);
			UE_LOG(LogTemp, Display, TEXT("Warrior 부딪힘"));
		}
		else if (GetPlayerClassType() == EPlayerClass::EWraith)
		{
			DefaultAttackComp->LoadAssetAsync(EAssetType::Wraith);
			UE_LOG(LogTemp, Display, TEXT("Wraith 부딪힘"));
		}
	}
}

APlayerController* ACSCharacterBase::GetMyController()
{
	return CastChecked<APlayerController>(GetController());
}

void ACSCharacterBase::DefaultAttack()
{
	UE_LOG(LogTemp, Display, TEXT("Parent Default Attack"));
}

void ACSCharacterBase::Run()
{
}

void ACSCharacterBase::Walk()
{
}

void ACSCharacterBase::Jump()
{
}

void ACSCharacterBase::EquipWeapon()
{
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

void ACSCharacterBase::QuickToSoul()
{
	if (GetPlayerClassType() == EPlayerClass::EWarrior)
	{
		DefaultAttackComp->UnLoadAsset(EAssetType::Warrior);
	}
	else if (GetPlayerClassType() == EPlayerClass::EWraith)
	{
		DefaultAttackComp->UnLoadAsset(EAssetType::Wraith);
	}

	ACodeStructureGameMode* GameMode = Cast<ACodeStructureGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->QuickToSoulInPlayer();
	}
}

