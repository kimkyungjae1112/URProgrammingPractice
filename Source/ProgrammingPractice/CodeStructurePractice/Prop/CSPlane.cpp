// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeStructurePractice/Prop/CSPlane.h"

ACSPlane::ACSPlane() : OriginRot(FRotator::ZeroRotator)
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = MeshComp;
}

void ACSPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator OneTargetRot(35.f, 0.f, 0.f);
	FRotator TwoTargetRot(-35.f, 0.f, 0.f);
	FRotator CurrentRot = GetActorRotation();

	if (bFlag)
	{
		SetActorRotation(FMath::RInterpConstantTo(CurrentRot, OneTargetRot, GetWorld()->GetDeltaSeconds(), 5.f));
		if (CurrentRot.Pitch >= 30.f) bFlag = false;
	}
	else
	{
		SetActorRotation(FMath::RInterpConstantTo(CurrentRot, TwoTargetRot, GetWorld()->GetDeltaSeconds(), 5.f));
		if (CurrentRot.Pitch <= -30.f) bFlag = true;
	}
}

