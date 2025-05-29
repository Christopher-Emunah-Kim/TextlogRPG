#pragma once
#include "BaseCharacter.h"
#include "../Util/Common.h"
#include "../Item/Item.h"
#include "../Item/EItemType.h"
#include <vector>

using namespace std;
class Item;

struct FPlayerData
{
	int32_t playerExperience = 0;
	int32_t playerMaxExperience = 100; // Experience needed to level up
	int32_t playerGold = 10000;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
	class MiscItem* miscOwned = nullptr;
};


class Player : public BaseCharacter
{
private:
	FPlayerData playerData;
	vector<Item*> inventory; 

public:
	//Default Constructor
	Player(const FPlayerData& data, const FCharacterInfo& info) : BaseCharacter(info), playerData(data) {}

	//Override functions
	virtual void TakeDamage(const BaseCharacter& target) override;
	virtual void Attack(BaseCharacter* target) override;

	//Specific functions
	static Player* CreateCharacter(const string& characterName);
	void SetName(const string& name);
	string GetName() const;
	FPlayerData GetPlayerData() const;
	
	void AddToInventory(class Item* item);
	vector<Item*> GetInventoryItems(EItemType type) const;
	void EquipItem(class Item* item);
	void LoseItem(class Item* item);
	void Heal(int32_t amount);
	void UseGold(int32_t amount);
	void EarnGold(int32_t amount);
	void GainLoot(int32_t experience, int32_t gold, class Item* item);
	//BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class


	////Destructor
	~Player();
};

