// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASPratice/Character/GCharacterBase.h"
#include "GEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGPRACTICE_API AGEnemyCharacter : public AGCharacterBase
{
	GENERATED_BODY()
	
public:
	AGEnemyCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
};
