#pragma once
#include "Area.h"
#include "DungeonStage.h"

enum class EBattleResult : uint8
{
	PLAYER_WIN,
	PLAYER_DEAD,
	PLAYER_RUN,
	_ERROR
};


class Monster;

class Dungeon : public Area 
{
public:
	Dungeon();
	Dungeon(const vector<vector<FMonsterInfo>>& stageMonsterInfo);
	~Dungeon();

private:
    vector<Monster*> vecDungeonMonsters;
	vector<DungeonStage*> vecDungeonStages;
	int16 currentStageIndex;

public:
	
	DungeonStage* GetCurrentStage() const;

	bool IsMoreStageLeft();

    virtual string GetAreaName() const override { return "Dungeon"; }

	virtual void Enter(Player* player) override;


    void AddMonster(Monster* monster);

    void RemoveMonster(Monster* monster);

	vector<Monster*>& GetMonsterList();

    EBattleResult EncounterMonster(Player* player, Monster* monster);

	
};