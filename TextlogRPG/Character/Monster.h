#pragma once
#include "BaseCharacter.h"
#include "CharacterInfo.h"

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
	Monster(const FMonsterInfo& info);

	// Override functions
	void TakeDamage(BaseCharacter& target) override;
	void Attack(BaseCharacter* target) override;

	// Destructor
	~Monster();


};
