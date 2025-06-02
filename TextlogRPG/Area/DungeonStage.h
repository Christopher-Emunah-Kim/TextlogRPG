#pragma once
#include "../Character/CharacterInfo.h"
#include "../Character/Monster.h"
#include "../Util/Common.h"



class DungeonStage
{
private:
	vector<FMonsterInfo> monsterInfoList;
	vector<class Monster*> monsterList;
	class MonsterPool* monsterPool;

public:
	DungeonStage(const vector<FMonsterInfo>& monsterInfos);
	
	void EnterStage();
	void ExitStage();

	vector<Monster*> GetMonsters();
	bool isCleared() const;

	void OnMonsterDefeat(Monster* monster);

	~DungeonStage();
};

