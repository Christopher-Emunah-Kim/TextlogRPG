#include "InventoryManager.h"


void InventoryManager::AddItem(Item* item) 
{

	vector<Item*>::iterator it = find(inventory.begin(), inventory.end(), item);
	if (item && it == inventory.end())
	{
        inventory.push_back(item);
	}
	else
	{
		Common::PrintSystemMsg("이미 보유 중인 아이템입니다.");
	}
}

void InventoryManager::RemoveItem(Item* item) 
{
    vector<Item*>::iterator it = std::find(inventory.begin(), inventory.end(), item);

    if (it != inventory.end()) 
		inventory.erase(it);
}

vector<Item*> InventoryManager::GetItemsByType(EItemType type) const 
{
    vector<Item*> result;

	for (size_t i = 0; i < inventory.size(); ++i)
	{
		Item* item = inventory[i];
		if (item->GetItemInfo().itemType == type)
		{
			result.push_back(item);
		}
	}
    return result;
}

const vector<Item*>& InventoryManager::GetAllItems() const 
{ 
	return inventory; 
}