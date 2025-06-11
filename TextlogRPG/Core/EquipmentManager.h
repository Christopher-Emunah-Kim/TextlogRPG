#pragma once
#include "../Item/EItemType.h"

class Weapon;
class Armor;
class MiscItem;
class Item;

class EquipmentManager
{
public:
	EquipmentManager() = default;
	~EquipmentManager() = default;

private:
	Weapon* pWeapon = nullptr;
	Armor* pArmor = nullptr;
	//MiscItem* pMiscItem = nullptr;

public:
	void Equip(Item* item);

	void Unequip(EItemType type);

	Weapon* GetWeapon() const;

	Armor* GetArmor() const;

	//MiscItem* GetMisc() const;

};