#pragma once
#include "BaseCharacter.h"
#include "../Character/CharacterInfo.h"
#include "../Util/Common.h"
#include "../Item/EItemType.h"
#include <vector>

using namespace std;


class Player : public BaseCharacter
{
public:
	//Default Constructor
	Player(const FPlayerInfo& data) : BaseCharacter(data), playerInfo(data) {}

private:
	FPlayerInfo playerInfo;
	vector<class Item*> inventory; 
	CharacterStatus baseStatus;
	CharacterStatus equipmentStatus;


public:
	virtual void TakeDamage(BaseCharacter& target) override;
	virtual void Attack(BaseCharacter* target) override;

	
	static Player* CreateCharacter(const string& characterName);
	
	void SetName(const string& name);
	string GetName() const;
	FPlayerInfo GetPlayerData() const;
	
	void AddToInventory(class Item* item);
	vector<Item*> GetInventoryItems(EItemType type) const;
	
	void EquipItem(class Item* item);
	void CaculateNewStatus(Item* item);
	void LoseItem(class Item* item);
	
	void Heal(int32 healAmount);
	
	void UseGold(int32 cost);
	void EarnGold(int32 earnGold);
	
	void GainLoot(int32 experience, int32 gold, class Item* item);
	void UpdateFinalStatus();

	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	
	void ShowPlayerStatus();

	////Destructor
	~Player();
};

