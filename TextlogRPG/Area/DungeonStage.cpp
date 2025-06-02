#include "DungeonStage.h"

DungeonStage::DungeonStage(const vector<FMonsterInfo>& monsterInfos)
	: monsterInfoList(monsterInfos)
{
}

void DungeonStage::EnterStage()
{
	monsterList.clear();
	for (const FMonsterInfo& info : monsterInfoList) 
	{
		monsterList.emplace_back(new Monster(info));
	}
}

void DungeonStage::ExitStage()
{
	monsterList.clear();
}

vector<Monster*> DungeonStage::GetMonsters()
{
	return monsterList;
}


DungeonStage::~DungeonStage()
{
	for (const Monster* monster : monsterList)
	{
		delete monster;
		monster = nullptr;
	}
	monsterInfoList.clear();
	monsterList.clear();
}