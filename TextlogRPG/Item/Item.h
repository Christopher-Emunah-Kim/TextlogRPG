#pragma once
#include <string>
#include <cstdint>
#include <iostream>
#include "EItemType.h"

using namespace std;
class Player;


struct FItemInfo
{
	EItemType itemType; 
	int32_t itemCost;
	int16_t attack;
	int16_t defense;
	int16_t agility;
	string itemName;

};


class Item abstract
{
private:
	FItemInfo itemInfo;

public:
	//Constructor
	Item() {	}

	Item(FItemInfo itemInfo)
		: itemInfo(itemInfo) {
		itemInfo.itemType = EItemType::NONE;
		itemInfo.itemCost = 10;
		itemInfo.attack = 1;
		itemInfo.defense = 1;
		itemInfo.agility = 1;
		itemInfo.itemName = "NONE";
	}

	virtual FItemInfo GetItemInfo() const { return itemInfo; }

	virtual Item& SetItem(EItemType type, int32_t cost, int16_t atk, int16_t def, int16_t agi, string name)
	{
		itemInfo.itemType = type;
		itemInfo.itemCost = cost;
		itemInfo.attack = atk;
		itemInfo.defense = def;
		itemInfo.agility = agi;
		itemInfo.itemName = name;
		return *this;
	}

	virtual void ShowItemInfo() const = 0;
	virtual void Use(Player* player) = 0;

	//Default Destructor
	virtual ~Item() = default; 
};
