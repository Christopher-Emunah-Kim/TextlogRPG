#include "../Util/common.h"

class CharacterStatus  
{  
private:  
	const int16_t attack;  
	const int16_t defense;  
	const int16_t agility;  

private:  
	CharacterStatus(int16_t atk, int16_t def, int16_t agi)  
		: attack{ atk }, defense{ def }, agility{ agi}  
	{	}  
public:  
	static CharacterStatus NewStatus(int16_t atk, int16_t def, int16_t agi);  

	CharacterStatus NewStatus(const CharacterStatus& other) const;  

	int32_t GetDamage(const CharacterStatus& other) const;

};
