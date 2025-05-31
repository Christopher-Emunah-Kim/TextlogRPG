#pragma once
#include "BaseCharacter.h"
#include "../Util/Common.h"
#include "../Item/EItemType.h"
#include <vector>

using namespace std;


struct FPlayerData
{
	int32_t playerExperience = 0;
	int32_t playerMaxExperience = 10; // Experience needed to level up
	int32_t playerGold = 10000;
	class Weapon* weaponEquipped = nullptr;
	class Armor* armorEquipped = nullptr;
	class MiscItem* miscOwned = nullptr;
};


class Player : public BaseCharacter
{
private:
	FPlayerData playerData;
	vector<class Item*> inventory; 

	CharacterStatus baseStatus;
	CharacterStatus equipmentStatus;

public:
	//Default Constructor
	Player(const FPlayerData& data, const FCharacterInfo& info) : BaseCharacter(info), playerData(data) {}

	//Override functions
	virtual void TakeDamage(BaseCharacter& target) override;
	virtual void Attack(BaseCharacter* target) override;

	
	static Player* CreateCharacter(const string& characterName);
	
	void SetName(const string& name);
	string GetName() const;
	FPlayerData GetPlayerData() const;
	
	void AddToInventory(class Item* item);
	vector<Item*> GetInventoryItems(EItemType type) const;
	
	void EquipItem(class Item* item);
	void LoseItem(class Item* item);
	
	void Heal(int32_t healAmount);
	
	void UseGold(int32_t cost);
	void EarnGold(int32_t earnGold);
	
	void GainLoot(int32_t experience, int32_t gold, class Item* item);
	void UpdateFinalStatus();

	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	
	void ShowPlayerStatus(Player* player);

	////Destructor
	~Player();
};

