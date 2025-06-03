#include "MonsterPool.h"
#include "../Character/Monster.h"



void MonsterPool::Initialize(const vector<FMonsterInfo>& monsterInfos, size_t countPerType)
{
	for (const FMonsterInfo& info : monsterInfos)
	{
		vector<Monster*>& vec = monsterPool[info.characterName];
		for (size_t i = 0; i < countPerType; ++i)
		{
			Monster* mon = new Monster(info);
			mon->GetCharacterInfo().health = mon->GetCharacterInfo().maxHealth;
			vec.emplace_back(mon);
		}
	}
}

Monster* MonsterPool::Acquire(const string& name)
{
	vector<Monster*>& vec = monsterPool[name];
	for (Monster* monster : vec) 
	{
		if (monster->GetCharacterInfo().health <= 0)
		{
			monster->GetCharacterInfo().health = monster->GetCharacterInfo().maxHealth;
			return monster;
		}
	}
	return nullptr;
}

void MonsterPool::Release(Monster* monster)
{
	monster->GetCharacterInfo().health = 0;
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