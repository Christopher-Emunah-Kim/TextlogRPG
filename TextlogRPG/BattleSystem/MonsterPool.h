#pragma once
#include "../Util/Common.h"
#include "../Character/Monster.h"
#include "../Character/CharacterInfo.h"

using namespace std;

class MonsterPool {
private:
	unordered_map<string, vector<Monster*>> monsterPool;

public:
	MonsterPool() {}
	~MonsterPool();

	void Initialize(const vector<FMonsterInfo>& monsterInfos, size_t countPerType);

	Monster* Acquire(const string& name);

	void Release(Monster* monster);


	
};
