#pragma once
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

class EquipmentManager 
{
private:
	Weapon* pWeapon = nullptr;
	Armor* pArmor = nullptr;
	MiscItem* pMiscItem = nullptr;

public:
    void Equip(Item* item);

    void Unequip(EItemType type);

    Weapon* GetWeapon() const;

    Armor* GetArmor() const;

    MiscItem* GetMisc() const;

};