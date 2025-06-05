#include "EquipmentManager.h"


void EquipmentManager::Equip(Item* item) 
{
    if (!item) return;
    switch (item->GetItemInfo().itemType) 
	{
        case EItemType::WEAPON: 
			pWeapon = dynamic_cast<Weapon*>(item); 
			break;
        case EItemType::ARMOR:
			pArmor = dynamic_cast<Armor*>(item); 
			break;
        case EItemType::MISC: 
			pMiscItem = dynamic_cast<MiscItem*>(item);
			break;

        default: break;
    }
}

void EquipmentManager::Unequip(EItemType type) 
{
    switch (type) 
	{
        case EItemType::WEAPON: 
			pWeapon = nullptr;
			break;
        case EItemType::ARMOR: 
			pArmor = nullptr; 
			break;
        case EItemType::MISC: 
			pMiscItem = nullptr; 
			break;

        default: break;
    }
}

Weapon* EquipmentManager::GetWeapon() const 
{
	return pWeapon; 
}

Armor* EquipmentManager::GetArmor() const 
{ 
	return pArmor; 
}

MiscItem* EquipmentManager::GetMisc() const 
{ 
	return pMiscItem; 
}