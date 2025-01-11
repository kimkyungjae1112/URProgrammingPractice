// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPratice/Character/GPlayerCharacter.h"
#include "GASPratice/AbilitySystem/GAbilitySystemComponent.h"
#include "GASPratice/Player/GPlayerState.h"
#include "GASPratice/Data/GInputDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AGPlayerCharacter::AGPlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void AGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &AGPlayerCharacter::Move);
	EnhancedInputComponent->BindAction(InputData->LookAction, ETriggerEvent::Triggered, this, &AGPlayerCharacter::Look);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(InputData->Q_Action, ETriggerEvent::Started, this, &AGPlayerCharacter::Test_Q);
}

// 서버에서 호출되는 함수.
// Pawn(캐릭터)이 컨트롤러에 소유 되었을 때 실행됨
// 이 시점에서 Pawn의 실제 주인이 정해지므로, 서버 측에서 ASC를 초기화 할 필요가 있음.
// 2025.1.11 21시 - 여기서 클라이언트에서만 실행? 작동? 하는 코드 작성시 오류
void AGPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Ability System을 초기화 하기 위함?
	InitAbilitySystemComponent();
}

// 클라이언트에서 PlayerState가 리플레케이션으로 갱신되었을 때, 혹은 처음으로 설정되었을 때 호출됨.
// PlayerState의 상태가 바뀌면 호출됨.
// PossessedBy, OnRep_PlayerState 두 곳에서 Init 함수를 호출하는 이유는, 
// 서버와 클라이언트가 같은 시점에 코드가 실행되지 않을 수 있으므로, 안전하게 각자의 타이밍에 호출하기 위함.
void AGPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Ability System을 초기화 하기 위함?
	InitAbilitySystemComponent();
	GiveDefaultAbilities();
}

void AGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputData->IMC, 0);
	}
}

void AGPlayerCharacter::InitAbilitySystemComponent()
{
	AGPlayerState* GPlayerState = GetPlayerState<AGPlayerState>();
	check(GPlayerState);

	AbilitySystemComponent = CastChecked<UGAbilitySystemComponent>(GPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(GPlayerState, this);
}

void AGPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void AGPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

void AGPlayerCharacter::Test_Q()
{
	AbilitySystemComponent->TryActivateAbilityByClass(DefaultAbilities[0]);
	UE_LOG(LogTemp, Display, TEXT("잘됨?"));
}

