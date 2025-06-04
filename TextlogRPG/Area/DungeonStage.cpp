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
	for (size_t i = 0; i< monsterInfoList.size(); ++i) 
	{
		const FMonsterInfo& info = monsterInfoList[i];
		Monster* mon = monsterPool->ActivateMonster(info.strCharacterName);
		if (!mon)
		{
			//Exception 
			mon = new Monster(info);

			mon->SetCurrentHealth(mon->GetCharacterInfo().iMaxHealth);
		}
		monsterList.push_back(mon);
		//monsterList.emplace_back(new Monster(info));
	}
}

void DungeonStage::ExitStage()
{
	for (size_t i = 0; i  < monsterList.size(); ++i)
	{
		monsterPool->DeactivateMonster(monsterList[i]);
	}

	monsterList.clear();
}

vector<Monster*> DungeonStage::GetMonsters()
{
	return monsterList;
}

bool DungeonStage::isCleared() const
{
	for (size_t i = 0; i < monsterList.size(); ++i)
	{
		Monster* pMonster = monsterList[i];
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