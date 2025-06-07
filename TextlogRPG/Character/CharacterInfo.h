#pragma once
#include "../Character/CharacterStatus.h"
#include "../Util/Common.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

class Weapon;
class Armor;
class MistItem;

struct FCharacterInfo
{
public:
	//Default Constructor
	FCharacterInfo() = default;

	//User-Defined Constructor
	FCharacterInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name)
		: characterStats(stats), iMaxHealth(maxHp), iCurrentHealth(hp), iCurrentLevel(lvl), strCharacterName(name) {
	}

public:
	CharacterStatus characterStats;
	int16 iCurrentLevel = 1;
	int32 iMaxHealth = 100;
	int32 iCurrentHealth = 100;
	string strCharacterName = "UNKNOWN";
};

struct FPlayerInfo : public FCharacterInfo
{

public:
	//Default Constructor
	FPlayerInfo() = default;

	//User-Defined Constructor
	FPlayerInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name,
		int32 exp = 0, int32 maxExp = 10, int32 gold = 10000,
		Weapon* weapon = nullptr, Armor* armor = nullptr, MiscItem* misc = nullptr)
		: FCharacterInfo(stats, maxHp, hp, lvl, name),
		playerExperience(exp), playerMaxExperience(maxExp), playerGold(gold),
		weaponEquipped(weapon), armorEquipped(armor), miscOwned(misc) {
	}

public:
	int32 playerExperience = 0;
	int32 playerMaxExperience = 15;
	int32 playerGold = 10000;
	Weapon* weaponEquipped = nullptr;
	Armor* armorEquipped = nullptr;
	MiscItem* miscOwned = nullptr;

};


struct FMonsterInfo : public FCharacterInfo
{
public:
	//Default Constructor
	FMonsterInfo() = default;

	//User-Defined Constructor
	FMonsterInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name, int32 exp, int32 gold)
		: FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold) {
	}

public:
	int32 dropExperience = 0;
	int32 dropGold = 0;

	
};
