#pragma once
#include "../Util/Common.h"
#include "../Item/Item.h"

class InventoryManager 
{
private:
	list<Item*> inventory;
	//vector<Item*> inventory;

public:
    void AddItem(Item* item);

    void RemoveItem(Item* item);

    list<Item*> GetItemsByType(EItemType type) const;

    const list<Item*>& GetAllItems() const;
};