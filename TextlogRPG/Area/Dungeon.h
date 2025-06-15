#pragma once
#include "BaseLevel.h"
#include "DungeonStage.h"

enum class EBattleResult : uint8
{
	PLAYER_WIN,
	PLAYER_DEAD,
	PLAYER_RUN,
	_ERROR
};

enum class EDungeonState : uint8
{
	ENTRANCE,
	BATTLE_PROMPT,
	IN_BATTLE,
	STAGE_CLEARED,
	LEAVING
};

class Monster;
class Player;
enum class EGameState;

class Dungeon : public BaseLevel 
{
public:
	Dungeon();
	Dungeon(const vector<vector<FMonsterInfo>>& stageMonsterInfo);
	~Dungeon();

private:
    vector<Monster*>		vecDungeonMonsters;
	vector<DungeonStage*>	vecDungeonStages;
	int16					currentStageIndex;

	EDungeonState			m_dungeonState = EDungeonState::ENTRANCE;
	Player*					m_player = nullptr;
	Monster*				m_currentMonster = nullptr;
	DungeonStage*			m_currentStage = nullptr;
	bool					m_bIsBattleInProgress = false;


public:
    virtual string			GetAreaName() const override { return "Dungeon"; }
	virtual void			Enter(Player* player) override;

protected:
	virtual void			ProcessInput(Player* player) override;
	virtual void			Update(float deltaTime) override;
	virtual void			Render() override;
	virtual bool			ShouldExit() override;
	virtual EGameState		GetNextState() override;
	
public:
	void					Initialize(Player* player);
	EGameState				Process(Player* player);
	void					Clear();

public:
    EBattleResult			EncounterMonster(Player* player, Monster* monster);

	DungeonStage*			GetCurrentStage() const;
	bool					IsMoreStageLeft();

    void					AddMonster(Monster* monster);
    void					RemoveMonster(Monster* monster);
	vector<Monster*>&		GetMonsterList();

private:
	void					CreateDungeonStages();
	void					RenderRunChoice();
	void					RenderWrongChoice();
	void					RenderGameOverMsg();
	void					InitiateBattle();
	void					ProcessBattleInput();
	//EGameState				ProcessBattleChoice(Player* player);
	//EGameState				BattleInStage(const vector<Monster*>& monsters, DungeonStage* stage, Player* player);

};