// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "CSGameInstance.generated.h"

class UWarriorAnimMontageDataAsset;
class UWraithAnimMontageDataAsset;

DECLARE_DELEGATE_OneParam(FOnWarriorDataAsyncLoad, UWarriorAnimMontageDataAsset*)
DECLARE_DELEGATE_OneParam(FOnWraithDataAsyncLoad, UWraithAnimMontageDataAsset*)

/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API UCSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCSGameInstance();

	FOnWarriorDataAsyncLoad OnWarriorDataAsyncLoad;
	FOnWraithDataAsyncLoad OnWraithDataAsyncLoad;

	virtual void Init() override;

	void WarriorAsyncLoad();
	void WraithAsyncLoad();

private:
	void WarriorDataLoad();
	void WraithDataLoad();

	static const FString WarriorPackageName;
	static const FString WraithPackageName;
	static const FString WarriorAnimMontageAssetName;
	static const FString WraithAnimMontageAssetName;

	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> Handle;

	FStreamableManager WraithStreamableManager;
	TSharedPtr<FStreamableHandle> WraithHandle;
};
