#include "DungeonStage.h"
#include "../BattleSystem/MonsterPool.h"

DungeonStage::DungeonStage(const vector<FMonsterInfo>& monsterInfos)
	: monsterInfoList(monsterInfos)
{
	monsterPool = new MonsterPool();
	monsterPool->Initialize(monsterInfos, 1);
}

void DungeonStage::EnterStage()
{
	monsterList.clear();
	for (const FMonsterInfo& info : monsterInfoList) 
	{
		Monster* mon = monsterPool->ActivateMonster(info.strCharacterName);
		if (!mon)
		{
			//Exception 
			mon = new Monster(info);

			mon->GetCharacterInfo().iCurrentHealth = mon->GetCharacterInfo().iMaxHealth;
		}
		monsterList.push_back(mon);
		//monsterList.emplace_back(new Monster(info));
	}
}

void DungeonStage::ExitStage()
{
	for (Monster* mon : monsterList)
	{
		monsterPool->DeactivateMonster(mon);
	}

	monsterList.clear();
}

vector<Monster*> DungeonStage::GetMonsters()
{
	return monsterList;
}

bool DungeonStage::isCleared() const
{
	for (Monster* mon : monsterList)
	{
		if (mon->GetCharacterInfo().iCurrentHealth > 0)
			return false;
	}
	return true;
}

void DungeonStage::OnMonsterDefeat(Monster* monster)
{
	if (monsterPool != nullptr)
	{
		monsterPool->DeactivateMonster(monster);
	}
}


DungeonStage::~DungeonStage()
{
	/*for (const Monster* monster : monsterList)
	{
		delete monster;
		monster = nullptr;
	}
	monsterInfoList.clear();
	monsterList.clear();*/
	ExitStage();
	delete monsterPool;
	monsterPool = nullptr;
}