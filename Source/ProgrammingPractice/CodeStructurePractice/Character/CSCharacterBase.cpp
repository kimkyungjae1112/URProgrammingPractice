// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Character/CSCharacterBase.h"

ACSCharacterBase::ACSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

