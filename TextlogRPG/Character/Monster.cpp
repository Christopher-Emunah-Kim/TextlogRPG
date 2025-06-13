#include "Monster.h"
#include "../Character/Player.h"
#include "../Core/ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

//Constructor
Monster::Monster(const FMonsterInfo& info)
	: fMonsterInfo(info), 
	m_monsterStatusComp(this),
	m_monsterCombatComp(this),
	m_monsterDropComp(this)
{
	Initialize(info);
}

void Monster::Initialize(const FMonsterInfo& info)
{
	

	m_monsterStatusComp.Initialize();
	m_monsterCombatComp.Initialize();

	m_monsterDropComp.Initialize();
	m_monsterDropComp.SetDropValues(info.dropExperience, info.dropGold);

	const vector<string>& itemNames = ItemManager::GetInstance().GetItemList();
	m_monsterDropComp.InitializeDropItems(itemNames);

}

void Monster::ApplyDamageFrom(BaseCharacter& attacker)
{
	m_monsterCombatComp.ApplyDamageFrom(attacker);


	if (m_monsterStatusComp.IsDefeated())
	{
		Player* playerAttacker = dynamic_cast<Player*>(&attacker);
		if (playerAttacker != nullptr && !m_monsterDropComp.GetDropItemNames().empty()) 
		{
			bool dropSuccess = m_monsterDropComp.ProcessItemDrop(playerAttacker);
			m_monsterDropComp.RenderItemDropResult(m_monsterDropComp.GetLastDropItem(), dropSuccess, playerAttacker);
		}
		Common::PauseAndClearScreen(2000);
	}
	
}

void Monster::Attack(BaseCharacter* target)
{
	

	m_monsterCombatComp.Attack(target);
	
}





void Monster::SetCurrentHealth(int32 health)
{
	
	m_monsterStatusComp.SetCurrentHealth(health);
}

void Monster::RenderMonsterStatus() const
{
	

	m_monsterStatusComp.RenderMonsterStatus();
}


Monster::~Monster()
{
	
}
