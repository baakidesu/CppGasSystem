// Copyright baakidesu


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultnfo UCharacterClassInfo::GetClassDefaultsInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
