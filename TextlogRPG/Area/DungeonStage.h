#pragma once
#include "../Character/CharacterInfo.h"
#include "../Character/Monster.h"
#include "../Util/Common.h"

class MonsterPool;
class Monster;

class DungeonStage
{
public:
	DungeonStage(const vector<FMonsterInfo>& monsterInfos);
	~DungeonStage();

private:
	vector<FMonsterInfo> monsterInfoList;
	vector<Monster*> monsterList;
	MonsterPool* monsterPool;

public:
	
	
	void EnterStage();
	void ExitStage();

	vector<Monster*> GetMonsters();
	bool isCleared() const;

	void OnMonsterDefeat(Monster* monster);
};

