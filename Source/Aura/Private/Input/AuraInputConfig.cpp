// Copyright baakidesu


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFount) const
{
	for (const FAuraInputAction& Action: AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFount)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag[%s], on InputConfig[%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
