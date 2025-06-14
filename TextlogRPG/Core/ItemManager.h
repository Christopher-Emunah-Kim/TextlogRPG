﻿#pragma once
#include "../Util/Common.h"
#include "../Item/item.h"

using namespace std;

class ItemManager
{
private:
	//item table : <name, item*>
	unordered_map<string, Item*> itemTableMap;

	//private constructor
	ItemManager() {}
	//delete copy constructor
	ItemManager(const ItemManager&) = delete;
	//Destructor
	~ItemManager();

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

	
};

