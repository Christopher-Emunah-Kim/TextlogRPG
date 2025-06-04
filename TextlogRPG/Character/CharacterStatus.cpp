#include "CharacterStatus.h"

CharacterStatus CharacterStatus::NewStatus(int16 atk, int16 def, int16 agi)
{
	return CharacterStatus(atk, def, agi);
}

CharacterStatus CharacterStatus::AddStatus(const CharacterStatus& other) const
{
	return CharacterStatus(	attack + other.attack,	defense + other.defense, agility + other.agility);
}

int32 CharacterStatus::CalculateDamage(const CharacterStatus& other) const
{
	int32 damage = other.GetAttack() - this->GetDefense();
	if (damage <= 0)
	{
		return 10;
	}
	else
	{
		return damage;
	}
}

