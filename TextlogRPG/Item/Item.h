#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include "../Character/Player.h" 

using namespace std;
/*
	3.0 class Item <abstract>
	3.0.0 string itemName
	3.0.1 int16 itemStats[3] itemStats //Attack, Defense, Agility
	3.0.2 enum class ItemType {WEAPON, ARMOR, MISC}
	3.0.3 ItemType itemType
	3.0.4 int32 itemCost
	3.0.5 void Use(Player* player) = 0

	3.1 class Wepon - Derived
	3.2 class Armor - Derived
	3.3 class MiscItem - Derived
*/

enum class EItemType
{
	WEAPON,
	ARMOR,
	MISC
};


class Item abstract
{
private:
	const string itemName;
	const int16_t itemStats[3]; // Attack, Defense, Agility
	const EItemType itemType;
	const int32_t itemCost;

public:
	//Constructor
	Item(const string& name = "Defulat", int16_t attack = 1, int16_t defense = 1, int16_t agility = 1, EItemType type = EItemType::MISC, int32_t cost = 1)
		: itemName(name), itemStats{ attack, defense, agility }, itemType(type), itemCost(cost) {	}

	//Getters
	virtual string getItemName() const { return itemName; }
	virtual int16_t getAttack() const { return itemStats[0]; }
	virtual int16_t getDefense() const { return itemStats[1]; }
	virtual int16_t getAgility() const { return itemStats[2]; }
	virtual EItemType getItemType() const { return itemType; }
	virtual int32_t getItemCost() const { return itemCost; }

	//Pure virtual functions
	virtual void getItemInfo() const = 0;
	virtual void Use(Player* player) = 0;

	//Default Destructor
	virtual ~Item() = default;
};

