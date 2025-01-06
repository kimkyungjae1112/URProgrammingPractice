// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WarriorDefaultAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWarriorDefaultAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMINGPRACTICE_API IWarriorDefaultAttackInterface
{
	GENERATED_BODY()

public:
	virtual void WarriorDefaultAttack() = 0;
};
