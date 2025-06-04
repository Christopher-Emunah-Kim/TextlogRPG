#pragma once
#include "../Util/Common.h"

class CharacterStatus  
{  
private:  
	const int16 attack;  
	const int16 defense;  
	const int16 agility;  

public:  
	CharacterStatus()  
		: attack{10}, defense{10}, agility{10}  
	{  
	}  

	CharacterStatus(int16 atk, int16 def, int16 agi)  
		: attack{atk}, defense{def}, agility{agi}  
	{  
	}  

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

