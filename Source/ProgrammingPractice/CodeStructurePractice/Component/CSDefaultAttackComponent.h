// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CodeStructurePractice/Interface/WraithDefaultAttackInterface.h"
#include "CodeStructurePractice/Interface/WarriorDefaultAttackInterface.h"
#include "CSDefaultAttackComponent.generated.h"

class UAnimInstance;
class ACharacter;
class UWarriorAnimMontageDataAsset;
class UWraithAnimMontageDataAsset;

UENUM()
enum class EAssetType : uint8
{
	Warrior,
	Wraith
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGPRACTICE_API UCSDefaultAttackComponent : public UActorComponent, 
	 public IWarriorDefaultAttackInterface, public IWraithDefaultAttackInterface
{
	GENERATED_BODY()

public:	
	UCSDefaultAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/* Interface Implement */
public:
	virtual void WarriorDefaultAttack() override;
	virtual void WraithDefaultAttack() override;

/* Asyncload */
public:
	void LoadAssetAsync(const EAssetType& AssetType);
	void UnLoadAsset(const EAssetType& AssetType);

/* Utility */
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACharacter> Player;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAnimInstance> Anim;

/* Asset Data */
private:
	static TObjectPtr<UWarriorAnimMontageDataAsset> WarriorAnimMontageDataAsset;
	static TObjectPtr<UWraithAnimMontageDataAsset> WraithAnimMontageDataAsset;

	void SetWarriorAnimMontageDataAsset(UWarriorAnimMontageDataAsset* InWarriorAnimMontageDataAsset);
	void SetWraithAnimMontageDataAsset(UWraithAnimMontageDataAsset* InWraithAnimMontageDataAsset);
};
