#pragma once
#include "../Item/EItemType.h"
#include "EquipSlot.h"
#include "../Util/Common.h"

class Weapon;
class Armor;
class MiscItem;
class Item;

class EquipmentManager
{
public:
	EquipmentManager();
	~EquipmentManager() = default;

private:
	//Weapon* pWeapon = nullptr;
	//Armor* pArmor = nullptr;
	//MiscItem* pMiscItem = nullptr;
	unordered_map<EItemType, EquipSlot> m_EquipSlots;


public:
	void Equip(Item* item);

	void Unequip(EItemType type);

	Weapon* GetWeapon() const;

	Armor* GetArmor() const;

	//MiscItem* GetMisc() const;

	Item* GetEquippedItem(EItemType slotType) const;

	bool HasEquippedItem(EItemType slotType) const;

};