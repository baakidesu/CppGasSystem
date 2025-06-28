// Copyright baakidesu


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbiltyActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag Tag : TagContainer)
	{
		//TODO:Broadcast the tag to the Widget Controller
		const FString Msg = FString::Printf(TEXT("Ability Loaded: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Red,Msg);
	}
}
