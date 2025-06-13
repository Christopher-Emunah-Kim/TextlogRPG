#pragma once
#include "../Item/EItemType.h"

class Item;

class EquipSlot
{
public:
    explicit EquipSlot(EItemType slotType);
    ~EquipSlot() = default;

private:
	EItemType	m_SlotType;
	Item*		m_EquippedItem = nullptr;

public:

    // equip/unequip
    void				Equip(Item* item);
    void				Unequip();
    
    // Check the equipped item
    inline Item*		GetEquippedItem() const { return m_EquippedItem; }
    inline bool			IsEquipped() const { return m_EquippedItem != nullptr; }
    
    // check the slot type
    inline EItemType	GetSlotType() const { return m_SlotType; }


};