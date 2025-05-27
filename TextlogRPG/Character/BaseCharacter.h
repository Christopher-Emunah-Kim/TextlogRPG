#pragma once
#include <string>
#include <cstdint>	
#include <iostream>

/* 
	[BaseCharacter]
	0.0 class BaseCharacter <abstract>
	0.0.0 int16 level
	0.0.1 int32 health
	0.0.2 int32 maxHealth
	0.0.3 string characterName
	0.0.4 int16 stats[3] #Attack, Defense, Agility
	0.0.5 void Heal(int32 amount) = 0
	0.0.6 void TakeDamage(int32 damage) = 0
	0.0.7 int16 GetAttack(BaseCharacter* character) = 0
	0.0.8 int16 GetDefense(BaseCharacter* character) = 0
	0.0.9 int16 GetAgility(BaseCharacter* character) = 0

	0.1 class Player - Derived
	0.0.0 int32 playerExperience
	0.0.1 int32 playerGold
	0.0.2 Weapon* weaponEquipped
	0.0.3 Armor* armorEquipped
	0.0.4 void LevelUp()
	0.0.5 void GainLoot(int32 experience, int32 gold, Item* item)
	0.0.6 void EquipItem(Item* item)

	0.2 class Monster - Derived
	0.2.0 int32 dropExperience
	0.2.1 vector<Item*> dropitems //weapon, armor, misc items
	0.2.2 void DropLoot(Player* player)
*/

using namespace std;

struct FCharacterInfo
{
	string charracterName = "Unknown";
	int32_t characterHealth = 100;
	int32_t characterMaxHealth = 100;
	int16_t characterLevel = 1;
};

struct FCharacterStats
{
	int16_t attack = 10;
	int16_t defense = 10;
	int16_t agility = 10;
};


class BaseCharacter abstract
{
private:
	//fix the member variables to structs
	FCharacterInfo characterInfo;
	FCharacterStats characterStats;


public:
	//Parameterized constructor
	BaseCharacter(const string& name = " ", int32_t health = 100, int32_t maxHealth= 100, int16_t level = 1, 
						int16_t attack=10, int16_t defense=10, int16_t agility=10)
		: characterInfo{ name, health, maxHealth, level }, characterStats{ attack, defense, agility }
	{
		cout << "The " << characterInfo.charracterName << " is created! " << endl;
	}
	
	//GETTER, SETTER functions optimized by using structs
	virtual FCharacterInfo GetCharacterInfo() const { return characterInfo; }
	virtual FCharacterStats GetCharacterStats() const { return characterStats; }
	virtual void SetCharacterInfo(const FCharacterInfo& info) { characterInfo = info; }
	virtual void SetCharacterStats(const FCharacterStats& stats) { characterStats = stats; }

	//Pure virtual functions
	virtual BaseCharacter& CreateCharacter(const string& characterName) = 0;
	virtual void TakeDamage(int32_t damage) = 0;
	virtual void Attack(BaseCharacter* target) = 0;

	//virtual destructor
	virtual ~BaseCharacter() = default;

};

