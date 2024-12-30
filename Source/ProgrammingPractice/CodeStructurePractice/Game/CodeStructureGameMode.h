// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeStructureGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API ACodeStructureGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACodeStructureGameMode();
	
protected:
	virtual void BeginPlay() override;

private:
	void ChangePlayer();
};
