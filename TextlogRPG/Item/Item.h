#pragma once
#include "../Util/Common.h"
#include "EItemType.h"
#include "../Character/CharacterStatus.h"

using namespace std;
class Player;


struct FItemInfo
{
	EItemType itemType = EItemType::NONE; 
	int32_t itemCost = 0;              
	int16_t attack = 0;                  
	int16_t defense = 0;               
	int16_t agility = 0;            
	string itemName = "UNKNOWN";

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

	//Default Destructor
	virtual ~Item() = default; 
};
