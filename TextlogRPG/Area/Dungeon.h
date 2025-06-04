#pragma once
#include "Area.h"
#include "DungeonStage.h"

class Monster;

class Dungeon : public Area 
{
private:
    vector<Monster*> monsters;
	vector<DungeonStage*> stages;
	int16 currentStageIndex;

public:
	Dungeon();
	Dungeon(vector<vector<FMonsterInfo>>& stageMonsterInfo);

	DungeonStage* GetCurrentStage();

	bool NextStage();

    string GetAreaName() const override { return "Dungeon"; }

    void Enter(Player* player) override;

    void AddMonster(Monster* monster);

    void RemoveMonster(Monster* monster);

	vector<Monster*>& GetMonsterList();

    bool EncounterMonster(Player* player, Monster* monster);

	~Dungeon();
};