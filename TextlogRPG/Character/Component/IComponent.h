#pragma once
#include "../Util/Common.h"

class BaseCharacter;
class Item;
class EquipmentManager;

//Base Interface
class IComponent
{
public:
    virtual ~IComponent() = default;
    
public:
    virtual void Initialize() = 0;
    
	virtual void Update() = 0;

    virtual void SetOwner(class Player* owner) = 0;
};

#pragma region Derived Component Interfaces

//Combat Component Interface
class ICombatComponent : public IComponent
{
public:
	// Update Functions
	virtual void Attack(BaseCharacter* target) = 0;
	virtual void ApplyDamageFrom(BaseCharacter& attacker) = 0;
	virtual int32 CalculateDamageFrom(const FCharacterInfo& targetCharacterInfo) = 0;
	virtual int32 UpdateDamage(BaseCharacter& attacker) = 0;
	virtual void UpdateAttack(BaseCharacter* target) = 0;

public:
	// Render Functions
	virtual void RenderAttackMessage(BaseCharacter* target) = 0;
	virtual void RenderDamageResult(BaseCharacter& attacker, int32 damage) = 0;
	virtual void DisplayDeathMessage() = 0;
	virtual void DisplayDamageMessage(BaseCharacter& attacker, int32 damage) = 0;
};


//Inventory Component Interface
class IInventoryComponent : public IComponent
{
public:
	// Update Functions
	virtual void AddItem(Item* item) = 0;
	virtual void RemoveItem(Item* item) = 0;
	virtual list<Item*> GetItemsByType(EItemType type) const = 0;
	virtual const list<Item*>& GetAllItems() const = 0;

	// Render Functions
	virtual void RenderItemAdded(class Item* item) = 0;
	virtual void RenderItemRemoved(class Item* item) = 0;
};


//Equipment Component Interface
class IEquipmentComponent : public IComponent
{
public:
	// Update Functions
	virtual void EquipItem(Item* item) = 0;
	virtual void UnequipItem(Item* item) = 0;
	virtual void UpdateEquipmentStatus() = 0;
	virtual Item* HandlePreviousEquipItem(Item* item) = 0;
	virtual void HandleMiscItem(Item* item) = 0;
	virtual const EquipmentManager& GetEquipmentManager() const = 0;

	// Render Functions
	virtual void RenderEquipMessage(Item* newItem) = 0;
	virtual void RenderMiscItemAdded(Item* item) = 0;
};


//Status Component Interface
class IStatusComponent : public IComponent
{
public:
	// Update Functions
	virtual void Heal(int32 healAmount) = 0;
	virtual void CharacterLevelUp() = 0;
	virtual void ProcessBonusStatusSelection() = 0;
	virtual void ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi) = 0;
	virtual void IncrementLevel() = 0;
	virtual void UpdateLevelDataPerLevel() = 0;
	virtual void UpdateFinalStatus() = 0;

	// Render Functions
	virtual void RenderLevelUpResult() = 0;
	virtual void RenderBonusStatusPrompt() = 0;
};

//Loot Component Interface
class ILootComponent : public IComponent
{
public:
	// Update Functions
	virtual void AddGold(int32 gold) = 0;
	virtual void UseGold(int32 cost) = 0;
	virtual void EarnGold(int32 earnGold) = 0;
	virtual void GainLoot(int32 experience, int32 gold, Item* item) = 0;
	virtual void AddExperience(int32 experience) = 0;
	virtual void ProcessLevelUp() = 0;
	virtual void UpdateLoot(int32 gold, int32 experience) = 0;
	virtual void UpdateGold(int32 earnGold) = 0;

	// Render Functions
	virtual void RenderGoldChange(int32 earnGold) = 0;
	virtual void RenderLootResult(int32 experience, int32 gold, Item* item) = 0;
};


//UI Component Interface
class IUIComponent : public IComponent
{
public:
	// Render Functions
	virtual void RenderPlayerStatus() const = 0;
	virtual string BuildPlayerStatusString() const = 0;
	virtual string BuildBasicInfoString() const = 0;
	virtual string BuildStatsString() const = 0;
	virtual string BuildEquipInfoString() const = 0;
	virtual string BuildInventoryString() const = 0;
};


#pragma endregion