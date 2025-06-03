#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "item.h"

using namespace std;

class ItemManager
{
private:
	//item table : <name, item*>
	unordered_map<string, Item*> itemTable;

	//private constructor
	ItemManager() {}
	//delete copy constructor
	ItemManager(const ItemManager&) = delete;

public:
	void InitializeItems();

	//Register Item
	void RegisterItem(Item* item);

	Item* CreateItem(const string& name);

	//Show item info by name
	void ShowItemInfo(const string& name);

	vector<string> GetItemList() const;

	//Get Item by name
	Item* GetItem(const string& name);

	//Use Static Instance
	static ItemManager& GetInstance();

	//Destructor
	~ItemManager();
};

