#include "DungeonStage.h"
#include "../BattleSystem/MonsterPool.h"

DungeonStage::DungeonStage(const vector<FMonsterInfo>& monsterInfos)
	: vecMonsterInfos(monsterInfos)
{
	monsterPool = new MonsterPool();
	monsterPool->Initialize(monsterInfos, 1);
}

void DungeonStage::EnterStage()
{
	vecStageMonsters.clear();
	for (size_t i = 0; i< vecMonsterInfos.size(); ++i) 
	{
		const FMonsterInfo& info = vecMonsterInfos[i];
		Monster* mon = monsterPool->ActivateMonster(info.strCharacterName);
		if (!mon)
		{
			//Exception 
			mon = new Monster(info);

			mon->SetCurrentHealth(mon->GetCharacterInfo().iMaxHealth);
		}
		vecStageMonsters.push_back(mon);
		//monsterList.emplace_back(new Monster(info));
	}
}

void DungeonStage::ExitStage()
{
	for (size_t i = 0; i  < vecStageMonsters.size(); ++i)
	{
		monsterPool->DeactivateMonster(vecStageMonsters[i]);
	}

	vecStageMonsters.clear();
}

vector<Monster*> DungeonStage::GetMonsters()
{
	return vecStageMonsters;
}

bool DungeonStage::isCleared() const
{
	for (size_t i = 0; i < vecStageMonsters.size(); ++i)
	{
		Monster* pMonster = vecStageMonsters[i];
		if (pMonster->GetCharacterInfo().iCurrentHealth > 0)
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
	ExitStage();
	delete monsterPool;
	monsterPool = nullptr;
}