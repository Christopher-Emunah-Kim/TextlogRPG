#pragma once
#include "../Util/Common.h"
#include "../Item/Item.h"

class InventoryManager 
{
private:
	vector<Item*> inventory;

public:
    void AddItem(Item* item);

    void RemoveItem(Item* item);

    vector<Item*> GetItemsByType(EItemType type) const;

    const vector<Item*>& GetAllItems() const;


};