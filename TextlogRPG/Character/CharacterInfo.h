#pragma once
#include "../Character/CharacterStatus.h"
#include "../Util/Common.h"



struct FCharacterInfo
{
	CharacterStatus characterStats;
	uint32 iMaxHealth = 100;
	uint32 iCurrentHealth = 100;
	uint16 iCurrentLevel = 1;
	string strCharacterName = "UNKNOWN";


	//Default Constructor
	FCharacterInfo() = default;

	//User-Defined Constructor
	FCharacterInfo(const CharacterStatus& stats, uint32 maxHp, uint32 hp, uint16 lvl, const string& name)
		: characterStats(stats), iMaxHealth(maxHp), iCurrentHealth(hp), iCurrentLevel(lvl), strCharacterName(name) {
	}
};

struct FPlayerData : public FCharacterInfo
{
	uint32 playerExperience = 0;
	uint32 playerMaxExperience = 15;
	uint32 playerGold = 10000;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
	class MiscItem* miscOwned = nullptr;

	//Default Constructor
	FPlayerData() = default;

	//User-Defined Constructor
	FPlayerData(const CharacterStatus& stats, uint32 maxHp, uint32 hp, uint16 lvl, const string& name,
		uint32 exp = 0, uint32 maxExp = 10, uint32 gold = 10000,
		Weapon* weapon = nullptr, Armor* armor = nullptr, MiscItem* misc = nullptr)
		: FCharacterInfo(stats, maxHp, hp, lvl, name),
		playerExperience(exp), playerMaxExperience(maxExp), playerGold(gold),
		weaponEquipped(weapon), armorEquipped(armor), miscOwned(misc) {
	}
};


struct FMonsterInfo : public FCharacterInfo
{
	uint32 dropExperience = 0;
	uint32 dropGold = 0;

	//Default Constructor
	FMonsterInfo() = default;

	//User-Defined Constructor
	FMonsterInfo(const CharacterStatus& stats, uint32 maxHp, uint32 hp, uint16 lvl, const string& name, uint32 exp, uint32 gold)
		: FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold) {
	}
};
