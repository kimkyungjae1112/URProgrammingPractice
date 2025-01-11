// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPratice/Character/GEnemyCharacter.h"
#include "GASPratice/AbilitySystem/GAbilitySystemComponent.h"

AGEnemyCharacter::AGEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AGEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
}
