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
	//생성자, 소멸자
	//Default Constructor
	Player(const FPlayerInfo& data);
	//Destructor
	~Player();

private:
	FPlayerInfo fPlayerInfo;
	CharacterStatus m_BaseStatus;
	CharacterStatus m_EquipmentStatus;
	InventoryManager m_inventoryManager;
	EquipmentManager m_EquipmentManager;


public:
	//Combat COmponent
	virtual void ApplyDamageFrom(BaseCharacter& target) override;
	void ProcessDamageResult(BaseCharacter& target, int32 iCalculatedDamage);
	void ProcessPlayerDeath();
	void DisplayDamageMessage(BaseCharacter& target, int32 iCalculatedDamage);
	void ApplyCaculatedDamage(int32 iCalculatedDamage);
	int32 CaculateDamageFrom(const FCharacterInfo& fTargetCharacterInfo);
	virtual void Attack(BaseCharacter* target) override;
	//Info Component
	virtual const FPlayerInfo& GetCharacterInfo() const override { return fPlayerInfo; }

public:
	//캐릭터 생성
	static Player* CreateCharacter(const string& characterName);


public:
	//Info Component?
	void SetName(const string& name);
	string GetName() const;
	FPlayerInfo GetPlayerData() const;

	//Status Component
	void Heal(int32 healAmount);
	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	void DisplayLevelUpResult();
	void ApplyBonusStatus();
	void ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi);
	void IncrementLevel();
	void ApplyLevelDataPerLevel();
	void UpdatePlayerStatus();

	//Inventory Component
	void AddToInventory(Item* item);
	list<Item*> GetInventoryItems(EItemType type) const;
	void LoseItem(Item* item);
	void UnequipItemIfEquipped(Item* item);
	void RemoveFromInventory(Item* item);

	//Equipment Component
	void EquipItem(Item* item);
	void PerformEquipItem(Item* previousItem, Item* newItem);
	Item* HandlePreviousEquipItem(Item* item);
	void HandleMiscItem(Item* item);
	const EquipmentManager& GetEquipmentManager() const;
	void UpdateEquipmentStatus();

	//Gold Component
	void UseGold(int32 cost);
	void EarnGold(int32 earnGold);
	
	//Reward
	void GainLoot(int32 experience, int32 gold, Item* item);
	void AddGold(int32 gold);
	void AddExperience(int32 experience);
	void ProcessLevelUp();

	

	//UI Comp
	void ShowPlayerStatus() const;
	string BuildPlayerStatusString() const;
	string BuildInventoryString() const;
	string BuildEquipInfoString() const;
	string BuildStatsString() const;
	string BuildBasicInfoString() const;


};

