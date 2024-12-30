// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Game/CodeStructureGameMode.h"
#include "CodeStructurePractice/Character/CSCharacterBase.h"
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
        UE_LOG(LogTemp, Display, TEXT("실행됨?"));

        TSubclassOf<APawn> NewPawnClass = Player->SelectedBySoul();
        if (!NewPawnClass)
        {
            UE_LOG(LogTemp, Error, TEXT("선택된 Pawn 클래스가 유효하지 않습니다!"));
            return;
        }

        DefaultPawnClass = NewPawnClass; 

        AController* PlayerController = Player->GetController();
        if (PlayerController)
        {
            Player->Destroy();
            RestartPlayer(PlayerController); 
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("플레이어 컨트롤러를 찾을 수 없습니다!"));
        }
    }
}
