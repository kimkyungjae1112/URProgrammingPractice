// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GCharacterBase.generated.h"

class UGAbilitySystemComponent;
class APlayerController;

UCLASS()
class PROGRAMMINGPRACTICE_API AGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGCharacterBase();

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// 캐릭터에게 기본 스킬을 부여하는 기능 함수
	void GiveDefaultAbilities();

	UPROPERTY()
	TObjectPtr<UGAbilitySystemComponent> AbilitySystemComponent;

	// 캐릭터가 기본적으로 부여받아야 할 능력들의 목록을 저장해둠.
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

protected:
	APlayerController* GetPlayerController();
};
