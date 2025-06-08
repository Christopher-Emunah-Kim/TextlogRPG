#pragma once
#include "../Util/EGameState.h"
#include <unordered_map>
#include <string>

constexpr __int32 DEFAULT_HEAL_COST = 15;
constexpr __int8   DEFAULT_NAMING_LENGTH = 20;

using namespace std;

class Player;
class Monster;
class Area;
class Dungeon;
class DungeonStage;


class GameManager 
{
public:
	GameManager(EGameState initialState, Player* player, Dungeon* dungeon);

	~GameManager();


private:
	EGameState gameState;
    Player* playerPtr;
	Dungeon* dungeonptr;
	unordered_map<EGameState, Area*> gameAreaMap;
    
public:
	void SetGameState(const EGameState& gs_in)	{ gameState = gs_in; }
	inline EGameState GetGameState() const 	{return gameState;	}

    void Run();

private:
	//Main Process of Game
	void InitializeGame();
	void InitializeDungeon();

	//InitializeGameMethods
	void WelcomMsg();
	void SetPlayerName();

	//RunProcess Methods
	void RunProcessTitle();
	void RunProcessVillage();
	void RunProcessDungeon();

	void BattleInDungeonStage(const vector<Monster*>& monsters, DungeonStage* stage);
	

	void GameOverProcess();

	
};