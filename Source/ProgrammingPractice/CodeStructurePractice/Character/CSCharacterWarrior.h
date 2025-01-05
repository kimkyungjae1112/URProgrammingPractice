// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "CSCharacterWarrior.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API ACSCharacterWarrior : public ACSCharacterBase
{
	GENERATED_BODY()
	
public:
	ACSCharacterWarrior();

/* Utility */
protected:
	virtual UClass* GetCharacterClass();
	
/* Input */
protected:
	virtual void DefaultAttack() override;
};
