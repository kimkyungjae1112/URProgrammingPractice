// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Game/CodeStructureGameMode.h"
#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "CodeStructurePractice/Character/CSCharacterSelectSoul.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ACodeStructureGameMode::ACodeStructureGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/ProgrammingPractice.CSPlayerController'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/BP_CSCharacterSelectSoul.BP_CSCharacterSelectSoul_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
}

void ACodeStructureGameMode::QuickSoulInPlayer()
{
	ACSCharacterSelectSoul* Soul = CastChecked<ACSCharacterSelectSoul>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSCharacterSelectSoul::StaticClass()));
	if (Soul)
	{
		TSubclassOf<APawn> NewPawnClass = Soul->StaticClass();
		if (!NewPawnClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Pawn 클래스가 유효하지 않음"));
			return;
		}

		APlayerController* Controller = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerControllerClass));
		if (!Controller)
		{
			UE_LOG(LogTemp, Error, TEXT("Controller 클래스가 유효하지 않음"));
			return;
		}

		DefaultPawnClass = Soul->StaticClass();
		Controller->Possess(Soul);

		Soul->RegisterInputSystem();
	}

}

void ACodeStructureGameMode::BeginPlay()
{
	Super::BeginPlay();

	ACSCharacterBase* Player = CastChecked<ACSCharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSCharacterBase::StaticClass()));
	if (Player)
	{
		Player->OnSignChangePlayer.BindUObject(this, &ACodeStructureGameMode::ChangePlayer);
	}
}

void ACodeStructureGameMode::ChangePlayer()
{
    ACSCharacterBase* Player = CastChecked<ACSCharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSCharacterBase::StaticClass()));
    if (Player)
    {
        TSubclassOf<APawn> NewPawnClass = Player->GetCharacterClass();
        if (!NewPawnClass)
        {
            UE_LOG(LogTemp, Error, TEXT("Pawn 클래스가 유효하지 않음"));
            return;
        }

		APlayerController* Controller = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerControllerClass));
		if (!Controller)
		{
			UE_LOG(LogTemp, Error, TEXT("Controller 클래스가 유효하지 않음"));
			return;
		}
        DefaultPawnClass = NewPawnClass; 
		Controller->Possess(Player);

		Player->RegisterInputSystem();
    }
}
