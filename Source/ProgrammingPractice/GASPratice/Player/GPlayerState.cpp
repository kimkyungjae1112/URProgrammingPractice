// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPratice/Player/GPlayerState.h"
#include "GASPratice/AbilitySystem/GAbilitySystemComponent.h"

AGPlayerState::AGPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
