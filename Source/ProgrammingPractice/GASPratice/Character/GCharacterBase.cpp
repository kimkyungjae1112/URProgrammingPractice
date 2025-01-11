// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPratice/Character/GCharacterBase.h"
#include "GASPratice/AbilitySystem/GAbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"

AGCharacterBase::AGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

UAbilitySystemComponent* AGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// DefaultAbilities 에 설정된 GameplayAbility 들을 서버에서만 순회하며
// 캐릭터의 AbilitySystemComponent 에 능력 스펙을 생성해서 부여함.
// 이러한 방식으로 캐릭터가 게임 시작 시 혹은 스폰 직후 필요한 "기본 스킬/능력"들을 자동으로 갖게됨.
void AGCharacterBase::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	// HasAuthority() -> 액터나 컴포넌트가 서버 권한을 가지고 있는지 여부를 판별하는 함수
	// true면 서버의 권한을 가진 상태 -> 현재 실행되는 로직이 서버 측에서 실행 중인지 결정함.
	// 서버는 게임 로직을 결정하고 데이터를 "진짜"로 수정할 수 있는 권한을 가지고,  클라이언트는 서버를 통해서만 상태를 갱신함.
	if (!HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		// GameplayAbility 를 실제로 부여하기 위한 "스펙"을 생성함.
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		// ASC 에 스펙을 넘겨주어, 해당 AbilityClass 를 기반으로 한 능력을 캐릭터에게 부여함.
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

APlayerController* AGCharacterBase::GetPlayerController()
{
	return CastChecked<APlayerController>(GetController());
}

