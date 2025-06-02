#pragma once
#include "../Character/CharacterStatus.h"
#include "../Util/Common.h"



struct FCharacterInfo
{
	CharacterStatus characterStats;
	int32_t maxHealth = 100;
	int32_t health = 100;
	int16_t level = 1;
	string characterName = "UNKNOWN";


	//Default Constructor
	FCharacterInfo() = default;

	//User-Defined Constructor
	FCharacterInfo(const CharacterStatus& stats, int32_t maxHp, int32_t hp, int16_t lvl, const string& name)
		: characterStats(stats), maxHealth(maxHp), health(hp), level(lvl), characterName(name) {
	}
};

struct FPlayerData : public FCharacterInfo
{
	int32_t playerExperience = 0;
	int32_t playerMaxExperience = 10;
	int32_t playerGold = 10000;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
	class MiscItem* miscOwned = nullptr;

	//Default Constructor
	FPlayerData() = default;

	//User-Defined Constructor
	FPlayerData(const CharacterStatus& stats, int32_t maxHp, int32_t hp, int16_t lvl, const string& name,
		int32_t exp = 0, int32_t maxExp = 10, int32_t gold = 10000,
		Weapon* weapon = nullptr, Armor* armor = nullptr, MiscItem* misc = nullptr)
		: FCharacterInfo(stats, maxHp, hp, lvl, name),
		playerExperience(exp), playerMaxExperience(maxExp), playerGold(gold),
		weaponEquipped(weapon), armorEquipped(armor), miscOwned(misc) {
	}
};


struct FMonsterInfo : public FCharacterInfo
{
	int32_t dropExperience = 0;
	int32_t dropGold = 0;

	//Default Constructor
	FMonsterInfo() = default;

	//User-Defined Constructor
	FMonsterInfo(const CharacterStatus& stats, int32_t maxHp, int32_t hp, int16_t lvl, const string& name, int32_t exp, int32_t gold)
		: FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold) {
	}
};
