#pragma once
#include "BaseCharacter.h"
#include "../Character/CharacterInfo.h"
#include "../Util/Common.h"
#include "../Item/EItemType.h"
#include "../Core/InventoryManager.h"
#include "../Core/EquipmentManager.h"


constexpr __int8 LEVELUP_BONUS = 2;

using namespace std;

class Item;

class Player : public BaseCharacter
{
public:
	//Default Constructor
	Player(const FPlayerInfo& data) : fPlayerInfo(data) {}
	//Destructor
	~Player();

private:
	FPlayerInfo fPlayerInfo;
	CharacterStatus m_BaseStatus;
	CharacterStatus m_EquipmentStatus;
	InventoryManager m_inventoryManager;
	EquipmentManager m_EquipmentManager;


public:
	virtual void ReceiveDamageFrom(BaseCharacter& target) override;
	virtual void Attack(BaseCharacter* target) override;
	const FPlayerInfo& GetCharacterInfo() const override { return fPlayerInfo; }
	
	static Player* CreateCharacter(const string& characterName);
	
	void SetName(const string& name);
	string GetName() const;
	FPlayerInfo GetPlayerData() const;
	
	void AddToInventory(Item* item);
	vector<Item*> GetInventoryItems(EItemType type) const;
	
	void EquipItem(Item* item);
	void UpdateEquipmentStatus();
	void LoseItem(Item* item);
	
	void Heal(int32 healAmount);
	
	void UseGold(int32 cost);
	void EarnGold(int32 earnGold);
	
	void GainLoot(int32 experience, int32 gold, Item* item);
	void UpdatePlayerStatus();

	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	
	void ShowPlayerStatus();

	
};

