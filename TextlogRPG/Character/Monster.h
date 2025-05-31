#pragma once
#include "BaseCharacter.h"

class Item;

class Monster : public BaseCharacter
{
private:
	int32_t dropExperience;
	int32_t dropGold;
	//vector<Item*> dropItems; // weapon, armor, misc items
	vector<string> dropItemList;
public:
	
	// User-Defined Constructor for Monster creation
	Monster(const string& name, int32_t health, int16_t attack, int16_t defense, int16_t agility, short level, int32_t exp, int32_t gold);

	// Override functions
	void TakeDamage(BaseCharacter& target) override;
	void Attack(BaseCharacter* target) override;

	// Destructor
	~Monster();


};
