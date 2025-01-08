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
	Handle = StreamableManager.RequestAsyncLoad(WraithSoftObjectPath, FStreamableDelegate::CreateUObject(this, &UCSGameInstance::WraithDataLoad));
}

void UCSGameInstance::UnloadWarriorAsset()
{
	const FString WarriorSoftObjectPath = FString::Printf(TEXT("%s.%s"), *WarriorPackageName, *WarriorAnimMontageAssetName);
	StreamableManager.Unload(WarriorSoftObjectPath);
}

void UCSGameInstance::UnloadWraithAsset()
{
	const FString WraithSoftObjectPath = FString::Printf(TEXT("%s.%s"), *WraithPackageName, *WraithAnimMontageAssetName);
	StreamableManager.Unload(WraithSoftObjectPath);
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
	if (Handle.IsValid() && Handle->HasLoadCompleted())
	{
		OnWraithDataAsyncLoad.ExecuteIfBound(Cast<UWraithAnimMontageDataAsset>(Handle->GetLoadedAsset()));
	}

	Handle->ReleaseHandle();
	Handle.Reset();
}
