#include "EquipSlot.h"
#include "../Item/Item.h"
#include "../Util/Common.h"

EquipSlot::EquipSlot(EItemType slotType)
    : m_SlotType(slotType), m_EquippedItem(nullptr)
{
}

void EquipSlot::Equip(Item* item)
{
    if (item == nullptr)
        return;
        
    // 이미 장착된 아이템이 있으면 해제
    if (IsEquipped())
    {
        Unequip();
    }
    
    m_EquippedItem = item;
}

void EquipSlot::Unequip()
{
    if (!IsEquipped())
    {
        Common::PrintErrorMsg("해제할 장비가 존재하지 않습니다.");
        return;
    }
    
    m_EquippedItem = nullptr;
}