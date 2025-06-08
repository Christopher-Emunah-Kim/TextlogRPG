#pragma once
#include "../Util/Common.h"

constexpr __int16 DEFAULT_ATTACK = 10;
constexpr __int16 DEFAULT_DEFENSE = 10;
constexpr __int16 DEFAULT_AGILITY = 10;


class CharacterStatus  
{  
public:
	CharacterStatus()
		: attack{ DEFAULT_ATTACK }, defense{ DEFAULT_DEFENSE }, agility{ DEFAULT_AGILITY }
	{
	}

	CharacterStatus(int16 atk, int16 def, int16 agi)
		: attack{ atk }, defense{ def }, agility{ agi }
	{
	}

private:  
	const int16 attack;  
	const int16 defense;  
	const int16 agility;  



public:

	static CharacterStatus NewStatus(int16 atk, int16 def, int16 agi);  

	CharacterStatus AddStatus(const CharacterStatus& other) const;  

	int32 CalculateDamage(const CharacterStatus& other) const;  

	//Get Status Info
	int16 GetAttack() const { return attack; }
	int16 GetDefense() const { return defense; }
	int16 GetAgility() const { return agility; }

	//operator = overloading
	CharacterStatus& operator=(const CharacterStatus& other)
	{
		if (this != &other)
		{
			const_cast<int16&>(attack) = other.attack;
			const_cast<int16&>(defense) = other.defense;
			const_cast<int16&>(agility) = other.agility;
		}
		return *this;
	}
};

