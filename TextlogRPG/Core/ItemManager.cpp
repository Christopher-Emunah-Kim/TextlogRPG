#include "ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"


void ItemManager::InitializeItems()
{
	//TODO : 드랍아이템 pool_ csv에서 불러오기 구현
	Weapon* basicSword = new Weapon();
	basicSword->SetItem(EItemType::WEAPON, 50, 3, 0, 0, "초보자의 검");
	Weapon* ironSword = new Weapon();
	ironSword->SetItem(EItemType::WEAPON, 80, 5, 0, 0, "철검");
	Weapon* woodenSword = new Weapon();
	woodenSword->SetItem(EItemType::WEAPON, 30, 2, 0, 0, "나무검");
	Armor* basicArmor = new Armor();
	basicArmor->SetItem(EItemType::ARMOR, 40, 0, 3, 0, "초보자의 갑옷");
	Armor* leatherArmor = new Armor();
	leatherArmor->SetItem(EItemType::ARMOR, 70, 0, 5, 2, "가죽갑옷");
	Armor* ironArmor = new Armor();
	ironArmor->SetItem(EItemType::ARMOR, 90, 0, 7, 1, "철갑옷");
	MiscItem* brokenCoin = new MiscItem();
	brokenCoin->SetItem(EItemType::MISC, 25, 0, 0, 0, "조각난 금화");
	MiscItem* littleBread = new MiscItem();
	littleBread->SetItem(EItemType::MISC, 10, 0, 0, 0, "작은 빵");

	RegisterItem(basicSword);
	RegisterItem(ironSword);
	RegisterItem(woodenSword);
	RegisterItem(basicArmor);
	RegisterItem(leatherArmor);
	RegisterItem(ironArmor);
	RegisterItem(brokenCoin);
	RegisterItem(littleBread);

}

void ItemManager::RegisterItem(Item* item)
{
	itemTableMap[item->GetItemInfo().itemName] = item;
}

Item* ItemManager::CreateItem(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTableMap.find(name);
	if (it != itemTableMap.end())
	{
		return it->second->CloneItem();
	}
	else
	{
		cout << "Not Available Item." << endl;
		return nullptr; 
	}
}

void ItemManager::ShowItemInfo(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTableMap.find(name);
	if (it != itemTableMap.end())
	{
		it->second->ShowItemInfo();
	}
	else
	{
		cout << "Not Available Item." << endl;
	}
}

vector<string> ItemManager::GetItemList() const
{
	vector<string> list;
	for (unordered_map<string, Item*>::const_iterator it = itemTableMap.begin(); it != itemTableMap.end(); ++it)
	{
		const pair<const string, Item*>& pair = *it;
		list.push_back(pair.first);
	}
	return list;
}

Item* ItemManager::GetItem(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTableMap.find(name); 
	return (it != itemTableMap.end()) ? it->second : nullptr;
}

ItemManager& ItemManager::GetInstance()
{
	static ItemManager instance; // static instance
	return instance;
}

ItemManager::~ItemManager()
{
	for (unordered_map<string, Item*>::const_iterator it = itemTableMap.begin(); it != itemTableMap.end(); ++it)
	{
		const pair<const string, Item*>& pair = *it;
		delete pair.second; 
	}

	itemTableMap.clear();
}
