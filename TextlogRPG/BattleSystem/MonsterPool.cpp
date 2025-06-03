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
			mon->GetCharacterInfo().iCurrentHealth = mon->GetCharacterInfo().iMaxHealth;
			vec.emplace_back(mon);
		}
	}
}

Monster* MonsterPool::Acquire(const string& name)
{
	vector<Monster*>& vec = monsterPool[name];
	for (Monster* monster : vec) 
	{
		if (monster->GetCharacterInfo().iCurrentHealth <= 0)
		{
			monster->GetCharacterInfo().iCurrentHealth = monster->GetCharacterInfo().iMaxHealth;
			return monster;
		}
	}
	return nullptr;
}

void MonsterPool::Release(Monster* monster)
{
	monster->GetCharacterInfo().iCurrentHealth = 0;
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