#pragma once
#include "../Character/CharacterStatus.h"
#include "../Util/Common.h"



struct FCharacterInfo
{
	CharacterStatus characterStats;
	int32 iMaxHealth = 100;
	int32 iCurrentHealth = 100;
	int16 iCurrentLevel = 1;
	string strCharacterName = "UNKNOWN";


	//Default Constructor
	FCharacterInfo() = default;

	//User-Defined Constructor
	FCharacterInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name)
		: characterStats(stats), iMaxHealth(maxHp), iCurrentHealth(hp), iCurrentLevel(lvl), strCharacterName(name) {
	}
};

struct FPlayerData : public FCharacterInfo
{
	int32 playerExperience = 0;
	int32 playerMaxExperience = 15;
	int32 playerGold = 10000;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
	class MiscItem* miscOwned = nullptr;

	//Default Constructor
	FPlayerData() = default;

	//User-Defined Constructor
	FPlayerData(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name,
		int32 exp = 0, int32 maxExp = 10, int32 gold = 10000,
		Weapon* weapon = nullptr, Armor* armor = nullptr, MiscItem* misc = nullptr)
		: FCharacterInfo(stats, maxHp, hp, lvl, name),
		playerExperience(exp), playerMaxExperience(maxExp), playerGold(gold),
		weaponEquipped(weapon), armorEquipped(armor), miscOwned(misc) {
	}
};


struct FMonsterInfo : public FCharacterInfo
{
	int32 dropExperience = 0;
	int32 dropGold = 0;

	//Default Constructor
	FMonsterInfo() = default;

	//User-Defined Constructor
	FMonsterInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name, int32 exp, int32 gold)
		: FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold) {
	}
};
