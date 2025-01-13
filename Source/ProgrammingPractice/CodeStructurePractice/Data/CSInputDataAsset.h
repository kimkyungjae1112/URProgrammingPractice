// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CSInputDataAsset.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROGRAMMINGPRACTICE_API UCSInputDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Input Context")
	TObjectPtr<UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> QuickSoulAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> DefaultAttackAction;

};
