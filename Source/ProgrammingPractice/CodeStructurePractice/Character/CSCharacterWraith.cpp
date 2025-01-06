// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterWraith.h"
#include "CodeStructurePractice/Component/CSDefaultAttackComponent.h"
#include "CodeStructurePractice/Interface/WraithDefaultAttackInterface.h"

ACSCharacterWraith::ACSCharacterWraith()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
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

EPlayerClass ACSCharacterWraith::GetPlayerClassType()
{
	return EPlayerClass::EWraith;
}

void ACSCharacterWraith::DefaultAttack()
{
	Super::DefaultAttack();

	UE_LOG(LogTemp, Display, TEXT("Wraith Default Attack"));

	IWraithDefaultAttackInterface* DefaultAttackInterface = Cast<IWraithDefaultAttackInterface>(DefaultAttackComp);
	if (DefaultAttackInterface)
	{
		DefaultAttackInterface->WraithDefaultAttack();
	}
}
