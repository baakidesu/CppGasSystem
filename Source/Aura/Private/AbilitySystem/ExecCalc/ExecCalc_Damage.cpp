// Copyright baakidesu


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get damage Set by Caller Attribute
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);


	//Capture blockchance on Target, and determine if there was a successful block.
	//if block halve the damage.
	float TargetBlockChance =  0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParams, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	if (bBlocked)
	{
		Damage = Damage / 2.f;
	}

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
