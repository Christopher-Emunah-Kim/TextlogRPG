#pragma once
#include "../Util/Common.h"

class CharacterStatus  
{  
private:  
	const uint16 attack;  
	const uint16 defense;  
	const uint16 agility;  

public:  
	CharacterStatus()  
		: attack{10}, defense{10}, agility{10}  
	{  
	}  

	CharacterStatus(uint16 atk, uint16 def, uint16 agi)  
		: attack{atk}, defense{def}, agility{agi}  
	{  
	}  

	static CharacterStatus NewStatus(uint16 atk, uint16 def, uint16 agi);  

	CharacterStatus AddStatus(const CharacterStatus& other) const;  

	uint32 CalculateDamage(const CharacterStatus& other) const;  

	//Get Status Info
	uint16 GetAttack() const { return attack; }
	uint16 GetDefense() const { return defense; }
	uint16 GetAgility() const { return agility; }

	//operator = overloading
	CharacterStatus& operator=(const CharacterStatus& other)
	{
		if (this != &other)
		{
			const_cast<uint16&>(attack) = other.attack;
			const_cast<uint16&>(defense) = other.defense;
			const_cast<uint16&>(agility) = other.agility;
		}
		return *this;
	}
};

