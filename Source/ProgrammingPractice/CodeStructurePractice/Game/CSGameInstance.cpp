// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Game/CSGameInstance.h"
#include "CodeStructurePractice/Data/WarriorAnimMontageDataAsset.h"
#include "CodeStructurePractice/Data/WraithAnimMontageDataAsset.h"

const FString UCSGameInstance::WarriorPackageName = TEXT("/Game/Data/DA_WarriorAnimMontage");
const FString UCSGameInstance::WraithPackageName = TEXT("/Game/Data/DA_WraithAnimMontage");
const FString UCSGameInstance::WarriorAnimMontageAssetName = TEXT("DA_WarriorAnimMontage");
const FString UCSGameInstance::WraithAnimMontageAssetName = TEXT("DA_WraithAnimMontage");

UCSGameInstance::UCSGameInstance()
{
}

void UCSGameInstance::Init()
{
	Super::Init();

}

void UCSGameInstance::WarriorAsyncLoad()
{
	const FString WarriorSoftObjectPath = FString::Printf(TEXT("%s.%s"), *WarriorPackageName, *WarriorAnimMontageAssetName);
	Handle = StreamableManager.RequestAsyncLoad(WarriorSoftObjectPath, FStreamableDelegate::CreateUObject(this, &UCSGameInstance::WarriorDataLoad));
}

void UCSGameInstance::WraithAsyncLoad()
{
	const FString WraithSoftObjectPath = FString::Printf(TEXT("%s.%s"), *WraithPackageName, *WraithAnimMontageAssetName);
	WraithHandle = WraithStreamableManager.RequestAsyncLoad(WraithSoftObjectPath, FStreamableDelegate::CreateUObject(this, &UCSGameInstance::WraithDataLoad));
}

void UCSGameInstance::WarriorDataLoad()
{
	if (Handle.IsValid() && Handle->HasLoadCompleted())
	{
		OnWarriorDataAsyncLoad.ExecuteIfBound(Cast<UWarriorAnimMontageDataAsset>(Handle->GetLoadedAsset()));
	}

	Handle->ReleaseHandle();
	Handle.Reset();
}

void UCSGameInstance::WraithDataLoad()
{
	if (WraithHandle.IsValid() && WraithHandle->HasLoadCompleted())
	{
		OnWraithDataAsyncLoad.ExecuteIfBound(Cast<UWraithAnimMontageDataAsset>(WraithHandle->GetLoadedAsset()));
	}

	WraithHandle->ReleaseHandle();
	WraithHandle.Reset();
}
