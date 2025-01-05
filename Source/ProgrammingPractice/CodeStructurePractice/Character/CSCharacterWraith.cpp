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

UClass* ACSCharacterWraith::GetCharacterClass()
{
	Super::GetCharacterClass();

	return StaticClass();
}

void ACSCharacterWraith::DefaultAttack()
{
	Super::DefaultAttack();

	UE_LOG(LogTemp, Display, TEXT("Wraith Default Attack"));
}
