#include "ItemManager.h"

void ItemManager::RegisterItem(Item* item)
{
	itemTable[item->getItemName()] = item;
}

void ItemManager::ShowItemInfo(const string& name)
{
	unordered_map<string, Item*>::iterator it = itemTable.find(name);
	if (it != itemTable.end())
	{
		it->second->getItemInfo();
	}
	else
	{
		cout << "Not Available Item." << endl;
	}
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
