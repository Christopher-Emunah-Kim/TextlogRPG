#pragma once
#include "BaseCharacter.h"

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

struct FPlayerData
{
	int32_t playerLevel = 1;
	int32_t playerExperience = 0;
	int32_t playerGoalExperience = 100; // Experience needed to level up
	int32_t playerGold = 0;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
};


class Player : public BaseCharacter
{
private:
	FPlayerData playerData;

public:
	//Default Constructor
	Player() : BaseCharacter(), playerData{} {
		cout << "Player created with default constructor." << endl;
	}

	//Parameterized Constructor
	Player(const string& name) : BaseCharacter(name), playerData{} {
		cout << "The " << name << " is created! " << endl;
	}

	//override functions
	virtual BaseCharacter& CreateCharacter(const string& characterName) override;
	virtual void TakeDamage(int32_t damage) override;
	virtual void Attack(BaseCharacter* target) override;

	////Specific functions
	//void EquipItem(class Item* item);
	//void Heal(int32_t amount);
	//void GainLoot(int32_t experience, int32_t gold, class Item* item);
	//BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class


	////Destructor
	~Player();
};

