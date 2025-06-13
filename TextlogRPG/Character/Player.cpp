#include "Player.h"
#include "../Character/CharacterStatus.h"
#include "../Item/Item.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "../LevelData/LevelData.h"



Player::Player(const FPlayerInfo& data)
	: fPlayerInfo(data),
	m_combatComp(this),
	m_statusComp(this),
	m_LootComp(this),
	m_equipmentComp(this),
	m_inventoryComp(this),
	m_UIComp(this)
{
	Initialize(data);
}

Player::~Player()
{
}

Player* Player::CreateCharacter()
{
	FPlayerInfo fTempCharacterInfo;
	return new Player(fTempCharacterInfo);
}

void Player::Initialize(const FPlayerInfo& data)
{
	fPlayerInfo = data;

	m_combatComp.Initialize();
	m_statusComp.Initialize();
	m_LootComp.Initialize();
	m_equipmentComp.Initialize();
	m_inventoryComp.Initialize();
	m_UIComp.Initialize();

	m_statusComp.UpdateFinalStatus();
}

void Player::Update()
{
	m_combatComp.Update();
	m_statusComp.Update();
	m_LootComp.Update();
	m_equipmentComp.Update();
	m_inventoryComp.Update();
	m_UIComp.Update();
}


void Player::ApplyDamageFrom(BaseCharacter& attacker)
{
	m_combatComp.ApplyDamageFrom(attacker);
}



void Player::Attack(BaseCharacter* target)
{
	m_combatComp.Attack(target);
}


void Player::SetName(const string& name)
{
	fPlayerInfo.strCharacterName = name;
}

string Player::GetName() const  
{  
    return fPlayerInfo.strCharacterName;
}



void Player::AddToInventory(Item* item)
{
	m_inventoryComp.AddItem(item);
}


list<Item*> Player::GetInventoryItems(EItemType type) const
{
	return m_inventoryComp.GetItemsByType(type);

}


void Player::EquipItem(Item* item)
{
	m_equipmentComp.EquipItem(item);
}


Item* Player::HandlePreviousEquipItem(Item* item)
{
	return m_equipmentComp.HandlePreviousEquipItem(item);
}

void Player::HandleMiscItem(Item* item)
{
	m_equipmentComp.HandleMiscItem(item);
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) 
		return;
	
	m_inventoryComp.RemoveItem(item);
	m_equipmentComp.UnequipItem(item);
	m_equipmentComp.UpdateEquipmentStatus();
	m_statusComp.UpdateFinalStatus();
}



void Player::ApplyHealing(int32 healAmount)
{

	m_statusComp.ApplyHealing(healAmount);
}

void Player::UseGold(int32 cost)
{
	
	m_LootComp.UseGold(cost);
}

void Player::EarnGold(int32 earnGold)
{
	m_LootComp.EarnGold(earnGold);
}

void Player::GainLoot(int32 experience, int32 gold, Item* item)
{

	m_LootComp.GainLoot(experience, gold, item);
}



void Player::AddGold(int32 gold)
{

	m_LootComp.AddGold(gold);
}

void Player::AddExperience(int32 experience)
{

	m_LootComp.AddExperience(experience);
}

void Player::ProcessLevelUp()
{
	

	m_LootComp.ProcessLevelUp();
}



BaseCharacter& Player::CharacterLevelUp()
{
	m_statusComp.CharacterLevelUp();

	return *this; 

}

void Player::RenderPlayerStatus() const
{

	m_UIComp.RenderPlayerStatus();
}

