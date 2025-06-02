#include "CharacterStatus.h"

CharacterStatus CharacterStatus::NewStatus(int16_t atk, int16_t def, int16_t agi)
{
	return CharacterStatus(atk, def, agi);
}

CharacterStatus CharacterStatus::NewStatus(const CharacterStatus& other) const
{
	return CharacterStatus(	attack + other.attack,	defense + other.defense, agility + other.agility);
}

int32_t CharacterStatus::GetDamage(const CharacterStatus& other) const
{
	int32_t damage = other.GetAttack() - this->GetDefense();
	return damage > 0 ? damage : 1;
}

