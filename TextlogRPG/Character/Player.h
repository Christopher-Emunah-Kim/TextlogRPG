﻿#pragma once
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
	FPlayerInfo				 fPlayerInfo;

	PlayerEquipmentComponent m_equipmentComp;
	PlayerInventoryComponent m_inventoryComp;
	PlayerCombatComponent	 m_combatComp;
	PlayerStatusComponent	 m_statusComp;
	PlayerLootComponent		 m_LootComp;
	PlayerUIComponent		 m_UIComp;


public:
	virtual void				ApplyDamageFrom(BaseCharacter& attacker) override;
	virtual void				Attack(BaseCharacter* target) override;
	virtual const FPlayerInfo&	GetCharacterInfo() const override { return fPlayerInfo; }


public:
	inline const PlayerEquipmentComponent&	GetEquipmentComponent() const { return m_equipmentComp; }
	inline const PlayerInventoryComponent&	GetInvetoryComponent() const { return m_inventoryComp; }
	inline const PlayerCombatComponent&		GetCombatComponent() const { return m_combatComp; }
	inline const PlayerLootComponent&		GetLootComponent() const { return m_LootComp; }
	inline const PlayerStatusComponent&		GetStatusComponent() const { return m_statusComp; }
	inline const PlayerUIComponent&			GetUIComponent() const { return m_UIComp; }

	inline const EquipmentManager&			GetEquipmentManager() const { return m_equipmentComp.GetEquipmentManager(); }

private:
	void			Initialize(const FPlayerInfo& data);
	
public:
	void			Update();
	static Player*	CreateCharacter();

public:
	void			SetName(const string& name);
	string			GetName() const;

	////Status Component Delegation
public:
	void			ApplyHealing(int32 healAmount);
	BaseCharacter&	CharacterLevelUp(); 

	////Inventory Component Delegation
public:
	void			AddToInventory(Item* item);
	list<Item*>		GetInventoryItems(EItemType type) const;

	////Equipment Component Delegation
public:
	void			EquipItem(Item* item);
	Item*			HandlePreviousEquipItem(Item* item);
	void			HandleMiscItem(Item* item);
	void			LoseItem(Item* item);

	////UI Component Delegation
public:
	void			RenderPlayerStatus() const;

	////Loot Component Delegation
public:
	void			UseGold(int32 cost);
	void			EarnGold(int32 earnGold);
	void			GainLoot(int32 experience, int32 gold, Item* item);
	void			AddGold(int32 gold);
	void			AddExperience(int32 experience);
	void			ProcessLevelUp();


};

