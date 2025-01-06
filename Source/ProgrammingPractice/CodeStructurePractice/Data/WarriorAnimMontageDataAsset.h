// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WarriorAnimMontageDataAsset.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API UWarriorAnimMontageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<UAnimMontage> DefaultAttackMontage;

	FORCEINLINE void Test()
	{
		UE_LOG(LogTemp, Warning, TEXT("Test Warrior Data Asset"));
	}
};
