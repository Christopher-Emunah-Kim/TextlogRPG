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
};
