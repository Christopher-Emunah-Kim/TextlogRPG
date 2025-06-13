#include "EquipmentManager.h"
#include "../Item/EItemType.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "EquipSlot.h"


EquipmentManager::EquipmentManager()
{
	m_EquipSlots.insert({ EItemType::WEAPON, EquipSlot(EItemType::WEAPON) });
	m_EquipSlots.insert({ EItemType::ARMOR, EquipSlot(EItemType::ARMOR) });
}


void EquipmentManager::Equip(Item* item)
{
	if (item == nullptr) 
		return;


	EItemType itemType = item->GetItemInfo().itemType;
	
	unordered_map<EItemType, EquipSlot>::iterator it = m_EquipSlots.find(itemType);
	if (it != m_EquipSlots.end())
	{
		it->second.Equip(item);
	}
}


void EquipmentManager::Unequip(EItemType type)
{
	unordered_map<EItemType, EquipSlot>::iterator it = m_EquipSlots.find(type);
	if (it != m_EquipSlots.end())
	{
		it->second.Unequip();
	}
}

Weapon* EquipmentManager::GetWeapon() const
{
	unordered_map<EItemType, EquipSlot>::const_iterator it = m_EquipSlots.find(EItemType::WEAPON);
	if(it!=m_EquipSlots.end() && it->second.IsEquipped())
	{
		return dynamic_cast<Weapon*>(it->second.GetEquippedItem());
	}

	return nullptr;
}

Armor* EquipmentManager::GetArmor() const
{
	unordered_map<EItemType, EquipSlot>::const_iterator it = m_EquipSlots.find(EItemType::ARMOR);

	if (it != m_EquipSlots.end() && it->second.IsEquipped())
	{
		return dynamic_cast<Armor*>(it->second.GetEquippedItem());
	}

	return nullptr;
}

Item* EquipmentManager::GetEquippedItem(EItemType slotType) const
{
	unordered_map<EItemType, EquipSlot>::const_iterator it = m_EquipSlots.find(slotType);

	if (it != m_EquipSlots.end() && it->second.IsEquipped())
	{
		return it->second.GetEquippedItem();
	}

	return nullptr;
}

bool EquipmentManager::HasEquippedItem(EItemType slotType) const
{
	unordered_map<EItemType, EquipSlot>::const_iterator it = m_EquipSlots.find(slotType);

	return (it != m_EquipSlots.end() && it->second.IsEquipped());
}

