#include "CharacterStatus.h"

CharacterStatus CharacterStatus::NewStatus(int16_t atk, int16_t def, int16_t agi)
{
	return CharacterStatus(atk, def, agi);
}

CharacterStatus CharacterStatus::NewStatus(const CharacterStatus& other) const
{
	return CharacterStatus(
		this->attack + other.attack,
		this->defense + other.defense,
		this->agility + other.agility
	);
}

int32_t CharacterStatus::GetDamage(const CharacterStatus& other) const
{
	return std::max<int32_t>(0, this->attack - other.defense);
}

