#include "PlayerInventoryComponent.h"
#include "../Player.h"
#include "../../Item/Item.h"

PlayerInventoryComponent::PlayerInventoryComponent(Player* owner)
    : m_owner(owner)
{
}

void PlayerInventoryComponent::Initialize()
{
    
}

void PlayerInventoryComponent::Update()
{
    
}

void PlayerInventoryComponent::SetOwner(Player* owner)
{
	m_owner = owner;
}

void PlayerInventoryComponent::AddItem(Item* item)
{
    if (item == nullptr)
        return;
        
	m_inventoryManager.AddItem(item);
    RenderItemAdded(item);
}

void PlayerInventoryComponent::RemoveItem(Item* item)
{
    if (item == nullptr)
        return;
        
	m_inventoryManager.RemoveItem(item);
    RenderItemRemoved(item);
}

list<Item*> PlayerInventoryComponent::GetItemsByType(EItemType type) const
{
    return m_inventoryManager.GetItemsByType(type);
}

const list<Item*>& PlayerInventoryComponent::GetAllItems() const
{
    return m_inventoryManager.GetAllItems();
}

void PlayerInventoryComponent::RenderItemAdded(Item* item)
{
    if (item != nullptr)
    {
        string message = item->GetItemInfo().itemName + "을(를) 인벤토리에 추가했습니다.";
        Common::PrintSystemMsg(message);
    }
}

void PlayerInventoryComponent::RenderItemRemoved(Item* item)
{
    if (item != nullptr)
    {
        string message = item->GetItemInfo().itemName + "을(를) 인벤토리에서 제거했습니다.";
        Common::PrintSystemMsg(message);
    }
}