#pragma once
#include "../Util/EGameState.h"
#include <unordered_map>
#include <string>


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
	unordered_map<EGameState, Area*> mapList;
    
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

	void BattleInDungeonStage(vector<Monster*> monsters, DungeonStage* stage);
	

	void GameOverProcess();

	
};