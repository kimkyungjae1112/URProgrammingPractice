// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Component/CSDefaultAttackComponent.h"

UCSDefaultAttackComponent::UCSDefaultAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCSDefaultAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCSDefaultAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

