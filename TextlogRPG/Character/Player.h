#pragma once
#include "BaseCharacter.h"
#include "../Character/CharacterInfo.h"
#include "../Util/Common.h"
#include "../Item/EItemType.h"
#include "../Core/InventoryManager.h"
#include "../Core/EquipmentManager.h"
#include "../Character/Component/PlayerEquipmentComponent.h"
#include "../Character/Component/PlayerInventoryComponent.h"




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
	PlayerEquipmentComponent m_equipmentComp;
	PlayerInventoryComponent m_inventoryComp;


public:
	//Combat COmponent
	virtual void ApplyDamageFrom(BaseCharacter& attacker) override;
	void RenderDamageResult(BaseCharacter& attacker, int32 damage);
	void DisplayDeathMessage();
	void DisplayDamageMessage(BaseCharacter& attacker, int32 damage);
	int32 CalculateDamageFrom(const FCharacterInfo& fTargetCharacterInfo);
	virtual void Attack(BaseCharacter* target) override;
	int32 UpdateDamage(BaseCharacter& attacker);
	void UpdateAttack(BaseCharacter* target);
	void RenderAttackMessage(BaseCharacter* target);

	//Info Component
	virtual const FPlayerInfo& GetCharacterInfo() const override { return fPlayerInfo; }

public:
	//캐릭터 생성
	static Player* CreateCharacter(const string& characterName);

	void Initialize(const FPlayerInfo& data);


public:
	//Info Component?
	void SetName(const string& name);
	string GetName() const;
	FPlayerInfo GetPlayerData() const;
	PlayerEquipmentComponent GetEquipmentComponent() const { return m_equipmentComp; }
	PlayerInventoryComponent GetInvetoryComponent() const { return m_inventoryComp; }

public:
	//Status Component
	void Heal(int32 healAmount);
	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	void RenderLevelUpResult();
	void ProcessBonusStatusSelection();
	void ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi);
	void IncrementLevel();
	void UpdateLevelDataPerLevel();
	void UpdateFinalStatus();

public:
	//Inventory Component
	void AddToInventory(Item* item);
	list<Item*> GetInventoryItems(EItemType type) const;
	void LoseItem(Item* item);
	void UnequipItem(Item* item);
	void RemoveFromInventory(Item* item);

public:
	//Equipment Component
	void EquipItem(Item* item);
	void UpdateEquipItem(Item* previousItem, Item* newItem);
	Item* HandlePreviousEquipItem(Item* item);
	void HandleMiscItem(Item* item);
	const EquipmentManager& GetEquipmentManager() const;
	void UpdateEquipmentStatus();
	void RenderEquipMessage(Item* newItem);

public:
	//Gold Component
	void UseGold(int32 cost);
	void EarnGold(int32 earnGold);
	
public:
	//Reward
	void GainLoot(int32 experience, int32 gold, Item* item);
	void AddGold(int32 gold);
	void AddExperience(int32 experience);
	void ProcessLevelUp();
	void UpdateLoot(int32 gold, int32 experience);
	void RenderLootResult(int32 experience, int32 gold, Item* item);
	void UpdateGold(int32 earnGold);
	void RenderGoldChange(int32 earnGold);
	void RenderBonusStatusPrompt();
	void UpdateBonusStatus(char statusChoice);
	void RenderMiscItemAdded(Item* item);
	
public:
	//UI Comp
	void RenderPlayerStatus() const;
	string BuildPlayerStatusString() const;
	string BuildInventoryString() const;
	string BuildEquipInfoString() const;
	string BuildStatsString() const;
	string BuildBasicInfoString() const;


};

