#ifndef CHARACTER_STATUS_H
#define CHARACTER_STATUS_H

#include "../Util/Common.h"

class CharacterStatus  
{  
private:  
	const int16_t attack;  
	const int16_t defense;  
	const int16_t agility;  

public:  
	CharacterStatus()  
		: attack{10}, defense{10}, agility{10}  
	{  
	}  

	CharacterStatus(int16_t atk, int16_t def, int16_t agi)  
		: attack{atk}, defense{def}, agility{agi}  
	{  
	}  

	static CharacterStatus NewStatus(int16_t atk, int16_t def, int16_t agi);  

	CharacterStatus NewStatus(const CharacterStatus& other) const;  

	int32_t GetDamage(const CharacterStatus& other) const;  

	//Get Status Info
	int16_t GetAttack() const { return attack; }
	int16_t GetDefense() const { return defense; }
	int16_t GetAgility() const { return agility; }

	//operator = overloading
	CharacterStatus& operator=(const CharacterStatus& other)
	{
		if (this != &other)
		{
			const_cast<int16_t&>(attack) = other.attack;
			const_cast<int16_t&>(defense) = other.defense;
			const_cast<int16_t&>(agility) = other.agility;
		}
		return *this;
	}
};


#endif // CHARACTER_STATUS_H