#include "BaseCharacter.h"

int16_t BaseCharacter::GetLevel(BaseCharacter* character) const
{
	return character->characterLevel;
}

int32_t BaseCharacter::GetHealth(BaseCharacter* character) const
{
	return character->characterHealth;
}

int16_t BaseCharacter::GetAttack(BaseCharacter* character) const
{
    return character->characterstats[0];
}

int16_t BaseCharacter::GetDefense(BaseCharacter* character) const
{
	return character->characterstats[1];
}

int16_t BaseCharacter::GetAgility(BaseCharacter* character) const
{
	return character->characterstats[2];
}


