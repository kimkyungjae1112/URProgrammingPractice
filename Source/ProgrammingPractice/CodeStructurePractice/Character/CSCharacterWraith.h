// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeStructurePractice/Character/CSCharacterBase.h"
#include "CSCharacterWraith.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API ACSCharacterWraith : public ACSCharacterBase
{
	GENERATED_BODY()

public:
	ACSCharacterWraith();

protected:
	virtual UClass* GetCharacterClass();
	
};
