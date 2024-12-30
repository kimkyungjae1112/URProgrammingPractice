// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterWraith.h"

ACSCharacterWraith::ACSCharacterWraith()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
}

UClass* ACSCharacterWraith::SelectedBySoul()
{
	Super::SelectedBySoul();

	UE_LOG(LogTemp, Display, TEXT("Child :: 닿았음"));
	return StaticClass();
}
