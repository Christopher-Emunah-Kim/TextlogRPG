#include "MonsterPool.h"
#include "../Character/Monster.h"



void MonsterPool::Initialize(const vector<FMonsterInfo>& monsterInfos, size_t countPerType)
{
	for (const FMonsterInfo& info : monsterInfos)
	{
		vector<Monster*>& vec = monsterPool[info.strCharacterName];
		for (size_t i = 0; i < countPerType; ++i)
		{
			Monster* mon = new Monster(info);
			ReviveMonster(mon);
			vec.push_back(mon);
		}
	}
}

Monster* MonsterPool::ActivateMonster(const string& name)
{
	vector<Monster*>& vec = monsterPool[name];
	for (Monster* monster : vec) 
	{
		if (monster->GetCharacterInfo().iCurrentHealth <= 0)
		{
			ReviveMonster(monster);
			return monster;
		}
	}
	return nullptr;
}

void MonsterPool::DeactivateMonster(Monster* monster)
{
	monster->SetCurrentHealth(0);
}

void MonsterPool::ReviveMonster(Monster* monster)
{
	monster->SetCurrentHealth(monster->GetCharacterInfo().iMaxHealth);
}

MonsterPool::~MonsterPool()
{
	for (pair<const string, vector<Monster*>>& pair : monsterPool)
	{
		for (Monster* mon : pair.second)
		{
			delete mon;
		}
		pair.second.clear();
	}
	monsterPool.clear();
}