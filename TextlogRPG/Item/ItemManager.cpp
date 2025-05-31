#include "ItemManager.h"
#include "Weapon.h"
#include "Armor.h"
#include "MiscItem.h"


void ItemManager::InitializeItems()
{
	//TODO : 몬스터의 드랍아이템 pool_ csv에서 불러오기 구현
	Weapon* basicSword = new Weapon();
	basicSword->SetItem(EItemType::WEAPON, 50, 10, 0, 0, "초보자의 검");
	Weapon* ironSword = new Weapon();
	ironSword->SetItem(EItemType::WEAPON, 80, 15, 0, 0, "철검");
	Armor* basicArmor = new Armor();
	basicArmor->SetItem(EItemType::ARMOR, 60, 0, 10, 0, "초보자의 갑옷");
	Armor* leatherArmor = new Armor();
	leatherArmor->SetItem(EItemType::ARMOR, 100, 0, 15, 2, "가죽갑옷");
	MiscItem* brokenCoin = new MiscItem();
	brokenCoin->SetItem(EItemType::MISC, 25, 0, 0, 0, "조각난 금화");
	MiscItem* littleBread = new MiscItem();
	littleBread->SetItem(EItemType::MISC, 10, 0, 0, 0, "작은 빵");

	RegisterItem(basicSword);
	RegisterItem(ironSword);
	RegisterItem(basicArmor);
	RegisterItem(leatherArmor);
	RegisterItem(brokenCoin);
	RegisterItem(littleBread);

}

void ItemManager::RegisterItem(Item* item)
{
	itemTable[item->GetItemInfo().itemName] = item;
}

Item* ItemManager::CreateItem(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTable.find(name);
	if (it != itemTable.end())
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
	unordered_map<string, Item*>::iterator it = itemTable.find(name);
	if (it != itemTable.end())
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
	for (const pair<const string, Item*>& pair : itemTable)
	{
		list.push_back(pair.first);
	}
	return list;
}

Item* ItemManager::GetItem(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTable.find(name); 
	return (it != itemTable.end()) ? it->second : nullptr;
}

ItemManager& ItemManager::GetInstance()
{
	static ItemManager instance; // static instance
	return instance;
}

ItemManager::~ItemManager()
{
	for (pair<const string, Item*>& pair : itemTable)
	{
		delete pair.second;
	}
	itemTable.clear();
}
