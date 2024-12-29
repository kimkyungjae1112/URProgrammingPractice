// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Game/CodeStructureGameMode.h"
#include "GameFramework/PlayerController.h"

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
