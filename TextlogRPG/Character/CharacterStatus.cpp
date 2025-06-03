#include "CharacterStatus.h"

CharacterStatus CharacterStatus::NewStatus(uint16 atk, uint16 def, uint16 agi)
{
	return CharacterStatus(atk, def, agi);
}

CharacterStatus CharacterStatus::NewStatus(const CharacterStatus& other) const
{
	return CharacterStatus(	attack + other.attack,	defense + other.defense, agility + other.agility);
}

uint32 CharacterStatus::GetDamage(const CharacterStatus& other) const
{
	uint32 damage = other.GetAttack() - this->GetDefense();
	return damage > 0 ? damage : 1;
}

