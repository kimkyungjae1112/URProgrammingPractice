// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterWarrior.h"

ACSCharacterWarrior::ACSCharacterWarrior()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
}

UClass* ACSCharacterWarrior::GetCharacterClass()
{
	Super::GetCharacterClass();

	return StaticClass();
}

void ACSCharacterWarrior::DefaultAttack()
{
	Super::DefaultAttack();

	UE_LOG(LogTemp, Display, TEXT("Warrior Default Attack"));
}
