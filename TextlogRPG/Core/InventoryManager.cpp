#include "InventoryManager.h"


void InventoryManager::AddItem(Item* item) 
{

	list<Item*>::iterator it = find(inventory.begin(), inventory.end(), item);
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
    list<Item*>::iterator it = std::find(inventory.begin(), inventory.end(), item);

	if (it != inventory.end())
	{
		inventory.erase(it);
	}
}

list<Item*> InventoryManager::GetItemsByType(EItemType type) const 
{
    list<Item*> result;

    for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it)
    {
        Item* item = *it;
        if (item->GetItemInfo().itemType == type)
        {
            result.push_back(item);
        }
    }
    return result;
}

const list<Item*>& InventoryManager::GetAllItems() const 
{ 
	return inventory; 
}