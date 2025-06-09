#pragma once
#include "../Character/CharacterStatus.h"
#include "../Util/Common.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"


constexpr __int16 DEFAULT_CHARACTER_LEVEL = 1;
constexpr __int16 DEFAULT_CHARACTER_MAX_LEVEL = 100; 
constexpr __int32 DEFAULT_CHARACTER_MAX_HEALTH = 100;
constexpr __int32 DEFAULT_CHARACTER_CURRENT_HEALTH = 100;
constexpr __int32 DEFAULT_PLAYER_EXPERIENCE = 0;
constexpr __int32 DEFAULT_PLAYER_MAX_EXPERIENCE = 15;
constexpr __int32 DEFAULT_PLAYER_GOLD = 1000;
constexpr __int32 DEFAULT_MONSTER_DROP_EXPERIENCE = 10;
constexpr __int32 DEFAULT_MONSTER_DROP_GOLD = 10;


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
	int16 iCurrentLevel = DEFAULT_CHARACTER_LEVEL;
	int32 iMaxHealth = DEFAULT_CHARACTER_MAX_HEALTH;
	int32 iCurrentHealth = DEFAULT_CHARACTER_CURRENT_HEALTH;
	string strCharacterName = "UNKNOWN";
};

struct FPlayerInfo : public FCharacterInfo
{

public:
	//Default Constructor
	FPlayerInfo() = default;

	//User-Defined Constructor
	FPlayerInfo(const CharacterStatus& stats, int32 maxHp, int32 hp, int16 lvl, const string& name,
		int32 exp = DEFAULT_PLAYER_EXPERIENCE, int32 maxExp = DEFAULT_PLAYER_MAX_EXPERIENCE, int32 gold = DEFAULT_PLAYER_GOLD,
		Weapon* weapon = nullptr, Armor* armor = nullptr, MiscItem* misc = nullptr)
		: FCharacterInfo(stats, maxHp, hp, lvl, name),
		playerExperience(exp), playerMaxExperience(maxExp), playerGold(gold)
		{	}

public:
	int32 playerExperience = DEFAULT_PLAYER_EXPERIENCE;
	int32 playerMaxExperience = DEFAULT_PLAYER_MAX_EXPERIENCE;
	int32 playerGold = DEFAULT_PLAYER_GOLD;

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
	int32 dropExperience = DEFAULT_MONSTER_DROP_EXPERIENCE;
	int32 dropGold = DEFAULT_MONSTER_DROP_GOLD;

	
};
