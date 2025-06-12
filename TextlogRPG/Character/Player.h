#pragma once
#include "BaseCharacter.h"

#include "../Character/CharacterInfo.h"
#include "../Util/Common.h"
#include "../Item/EItemType.h"

#include "../Core/InventoryManager.h"
#include "../Core/EquipmentManager.h"

#include "../Character/Component/PlayerEquipmentComponent.h"
#include "../Character/Component/PlayerInventoryComponent.h"
#include "../Character/Component/PlayerCombatComponent.h"
#include "../Character/Component/PlayerLootComponent.h"
#include "../Character/Component/PlayerStatusComponent.h"
#include "../Character/Component/PlayerUIComponent.h"





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

	//CharacterStatus m_BaseStatus;
	//CharacterStatus m_EquipmentStatus;

	//InventoryManager m_inventoryManager;
	//EquipmentManager m_EquipmentManager;

	PlayerEquipmentComponent m_equipmentComp;
	PlayerInventoryComponent m_inventoryComp;
	PlayerCombatComponent	 m_combatComp;
	PlayerStatusComponent	 m_statusComp;
	PlayerLootComponent		 m_LootComp;
	PlayerUIComponent		 m_UIComp;


public:
	virtual void ApplyDamageFrom(BaseCharacter& attacker) override;
	virtual void Attack(BaseCharacter* target) override;
	virtual const FPlayerInfo& GetCharacterInfo() const override { return fPlayerInfo; }


public:
	void Initialize(const FPlayerInfo& data);
	void Update();

	//캐릭터 생성
	static Player* CreateCharacter();


public:
	void SetName(const string& name);
	string GetName() const;


public:
    inline const PlayerEquipmentComponent& GetEquipmentComponent() const { return m_equipmentComp; }
	inline const PlayerInventoryComponent& GetInvetoryComponent() const { return m_inventoryComp; }
	inline const PlayerCombatComponent& GetCombatComponent() const { return m_combatComp; }
	inline const PlayerLootComponent& GetLootComponent() const { return m_LootComp; }
	inline const PlayerStatusComponent& GetStatusComponent() const { return m_statusComp; }
	inline const PlayerUIComponent& GetUIComponent() const { return m_UIComp; }


	inline const EquipmentManager& GetEquipmentManager() const { return m_equipmentComp.GetEquipmentManager(); }


public:
	//Status Component Delegation
	void Heal(int32 healAmount);
	BaseCharacter& CharacterLevelUp(); //Player status update with Level Data class
	//void UpdateFinalStatus();


	//void RenderLevelUpResult();
	//void ProcessBonusStatusSelection();
	//void ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi);
	//void IncrementLevel();
	//void UpdateLevelDataPerLevel();
	//void RenderBonusStatusPrompt();
	//void UpdateBonusStatus(char statusChoice);


public:
	//Inventory Component Delegation
	void AddToInventory(Item* item);
	list<Item*> GetInventoryItems(EItemType type) const;
	//void RemoveFromInventory(Item* item);

public:
	//Equipment Component Delegation
	void EquipItem(Item* item);
	//void UnequipItem(Item* item);
	//void UpdateEquipmentStatus();
	Item* HandlePreviousEquipItem(Item* item);
	void HandleMiscItem(Item* item);

	void LoseItem(Item* item);


	//void UpdateEquipItem(Item* previousItem, Item* newItem);
	//void RenderEquipMessage(Item* newItem);

public:
	//Loot Component Delegation
	void UseGold(int32 cost);
	void EarnGold(int32 earnGold);
	void GainLoot(int32 experience, int32 gold, Item* item);
	void AddGold(int32 gold);
	void AddExperience(int32 experience);
	void ProcessLevelUp();
	//void UpdateLoot(int32 gold, int32 experience);
	//void RenderLootResult(int32 experience, int32 gold, Item* item);
	//void UpdateGold(int32 earnGold);
	//void RenderGoldChange(int32 earnGold);
	//void RenderMiscItemAdded(Item* item);

public:
	//UI Comp
	void RenderPlayerStatus() const;
	/*string BuildPlayerStatusString() const;
	string BuildInventoryString() const;
	string BuildEquipInfoString() const;
	string BuildStatsString() const;
	string BuildBasicInfoString() const;*/




public:

	//void RenderDamageResult(BaseCharacter& attacker, int32 damage);
	//void DisplayDeathMessage();
	//void DisplayDamageMessage(BaseCharacter& attacker, int32 damage);
	//int32 CalculateDamageFrom(const FCharacterInfo& fTargetCharacterInfo);
	//int32 UpdateDamage(BaseCharacter& attacker);
	//void UpdateAttack(BaseCharacter* target);
	//void RenderAttackMessage(BaseCharacter* target);

	


};

