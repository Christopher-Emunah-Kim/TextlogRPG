#pragma once
#include "../Util/Common.h"
#include "EItemType.h"
#include "../Character/CharacterStatus.h"

using namespace std;
class Player;

constexpr __int32 DEFAULT_ITEM_COST = 10;
constexpr __int16 DEFAULT_ITEM_ATTACK = 1;
constexpr __int16 DEFAULT_ITEM_DEFENSE = 1;
constexpr __int16 DEFAULT_ITEM_AGILITY = 1;


struct FItemInfo
{
	EItemType itemType = EItemType::NONE; 
	int32 itemCost = DEFAULT_ITEM_COST;
	int16 attack = DEFAULT_ITEM_ATTACK;
	int16 defense = DEFAULT_ITEM_DEFENSE;
	int16 agility = DEFAULT_ITEM_AGILITY;
	string itemName = "UNKNOWN";

};


class Item abstract
{
public:
	//Constructor
	Item() {}

	Item(FItemInfo itemInfo)
		: itemInfo(itemInfo) {	}

	//Default Destructor
	virtual ~Item() = default;

private:
	FItemInfo itemInfo;

public:
	

	virtual FItemInfo GetItemInfo() const { return itemInfo; }

	virtual Item& SetItem(EItemType type, int32 cost, int16 atk, int16 def, int16 agi, string name)
	{
		itemInfo.itemType = type;
		itemInfo.itemCost = cost;
		itemInfo.attack = atk;
		itemInfo.defense = def;
		itemInfo.agility = agi;
		itemInfo.itemName = name;
		return *this;
	}

	virtual string GetItemName() const { return itemInfo.itemName; }
	
	virtual void ShowItemInfo() const
	{
		string strItemInfo = "아이템명: " + GetItemInfo().itemName +
			" ( ATK : " + to_string(GetItemInfo().attack) +
			", DEF : " + to_string(GetItemInfo().defense) +
			", AGI : " + to_string(GetItemInfo().agility) + " )";

		Common::PrintInfoMsg(strItemInfo);
	}

	//Pure virtual functions
	virtual Item* CloneItem() const = 0;
	virtual void EquippedBy(Player* player) = 0;

};
