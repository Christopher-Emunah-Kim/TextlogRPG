#pragma once
#include "BaseCharacter.h"
#include "CharacterInfo.h"

class Item;

class Monster : public BaseCharacter
{
public:
	// User-Defined Constructor for Monster creation
	Monster(const FMonsterInfo& info);
	// Destructor
	~Monster();

private:
	int32 dropExperience;
	int32 dropGold;
	//vector<Item*> dropItems; // weapon, armor, misc items
	vector<string> dropItemList;
	FMonsterInfo fMonsterInfo;


public:
	// Override functions
	const FCharacterInfo& GetCharacterInfo() const override { return fMonsterInfo; }
	virtual void ReceiveDamageFrom(BaseCharacter& target) override;
	virtual void Attack(BaseCharacter* target) override;


	void SetCurrentHealth(int32 health);
	void ShowMonsterStatus();

};
