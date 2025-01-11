// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GPlayerState.generated.h"

class UGAbilitySystemComponent;

UCLASS()
class PROGRAMMINGPRACTICE_API AGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UPROPERTY()
	TObjectPtr<UGAbilitySystemComponent> AbilitySystemComponent;
};
