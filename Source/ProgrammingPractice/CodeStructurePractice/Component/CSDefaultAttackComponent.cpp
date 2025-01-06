// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Component/CSDefaultAttackComponent.h"
#include "CodeStructurePractice/Data/WarriorAnimMontageDataAsset.h"
#include "CodeStructurePractice/Data/WraithAnimMontageDataAsset.h"
#include "CodeStructurePractice/Game/CSGameInstance.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

UCSDefaultAttackComponent::UCSDefaultAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCSDefaultAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<ACharacter>(GetOwner());
	Anim = Player->GetMesh()->GetAnimInstance();
	ensure(Anim);

	UCSGameInstance* GameInstance = Cast<UCSGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnWarriorDataAsyncLoad.BindUObject(this, &UCSDefaultAttackComponent::SetWarriorAnimMontageDataAsset);
		GameInstance->OnWraithDataAsyncLoad.BindUObject(this, &UCSDefaultAttackComponent::SetWraithAnimMontageDataAsset);
	}
}


void UCSDefaultAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCSDefaultAttackComponent::WarriorDefaultAttack()
{
	Anim->Montage_Play(WarriorAnimMontageDataAsset->DefaultAttackMontage);
}

void UCSDefaultAttackComponent::WraithDefaultAttack()
{
	Anim->Montage_Play(WraithAnimMontageDataAsset->DefaultAttackMontage);
}

void UCSDefaultAttackComponent::LoadAssetAsync(const EAssetType& AssetType)
{
	UCSGameInstance* GameInstance = Cast<UCSGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		if (AssetType == EAssetType::Warrior)
		{
			GameInstance->WarriorAsyncLoad();
		}
		else if (AssetType == EAssetType::Wraith)
		{
			GameInstance->WraithAsyncLoad();
		}
	}
}

void UCSDefaultAttackComponent::SetWarriorAnimMontageDataAsset(UWarriorAnimMontageDataAsset* InWarriorAnimMontageDataAsset)
{
	WarriorAnimMontageDataAsset = InWarriorAnimMontageDataAsset;
}

void UCSDefaultAttackComponent::SetWraithAnimMontageDataAsset(UWraithAnimMontageDataAsset* InWraithAnimMontageDataAsset)
{
	WraithAnimMontageDataAsset = InWraithAnimMontageDataAsset;
}

