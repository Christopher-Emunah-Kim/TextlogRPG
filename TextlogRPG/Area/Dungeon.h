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
enum class EGameState;

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
    virtual string GetAreaName() const override { return "Dungeon"; }
	virtual void Enter(Player* player) override;
	
public:
	void Initialize(Player* player);
	EGameState Process(Player* player);
	void Clear();

public:
    EBattleResult EncounterMonster(Player* player, Monster* monster);

	DungeonStage* GetCurrentStage() const;
	bool IsMoreStageLeft();

    void AddMonster(Monster* monster);
    void RemoveMonster(Monster* monster);
	vector<Monster*>& GetMonsterList();

private:
	void CreateDungeonStages();
	EGameState HandleChoice(char dungeonChoice, Player* player);
	EGameState ProcessBattleChoice(Player* player);
	void RenderRunChoice();
	void RenderWrongChoice();
	EGameState BattleInStage(const vector<Monster*>& monsters, DungeonStage* stage, Player* player);
	void RenderGameOverMsg();
};