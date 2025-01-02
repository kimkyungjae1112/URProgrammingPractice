// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSPlane.generated.h"

UCLASS()
class PROGRAMMINGPRACTICE_API ACSPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSPlane();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	FRotator OriginRot;
	bool bFlag = true;
};
