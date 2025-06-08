#include "MonsterPool.h"
#include "../Character/Monster.h"



void MonsterPool::Initialize(const vector<FMonsterInfo>& monsterInfos, size_t countPerType)
{
	for (size_t idx = 0; idx < monsterInfos.size(); ++idx)
	{
		const FMonsterInfo& info = monsterInfos[idx];
		vector<Monster*>& vec = monsterPoolMap[info.strCharacterName];
		for (size_t i = 0; i < countPerType; ++i)
		{
			Monster* pMonster = new Monster(info);
			ReviveMonster(pMonster);
			vec.push_back(pMonster);
		}
	}
}

Monster* MonsterPool::ActivateMonster(const string& name)
{
	const vector<Monster*>& vec = monsterPoolMap[name];
	for (size_t i = 0; i < vec.size(); ++i) 
	{
		Monster* pMonster = vec[i];
		if (pMonster->GetCharacterInfo().iCurrentHealth <= 0)
		{
			ReviveMonster(pMonster);
			return pMonster;
		}
	}
	return nullptr;
}

void MonsterPool::DeactivateMonster(Monster* pMonster)
{
	pMonster->SetCurrentHealth(0);
}

void MonsterPool::ReviveMonster(Monster* pMonster)
{
	pMonster->SetCurrentHealth(pMonster->GetCharacterInfo().iMaxHealth);
}

MonsterPool::~MonsterPool()
{
	for (unordered_map<string, vector<Monster*>>::iterator it = monsterPoolMap.begin(); it != monsterPoolMap.end();++it)
	{
		vector<Monster*>& monsterList = it->second;
		for (size_t i = 0; i < monsterList.size(); ++i)
		{
			delete monsterList[i];
		}
		it->second.clear();
	}
	monsterPoolMap.clear();
}