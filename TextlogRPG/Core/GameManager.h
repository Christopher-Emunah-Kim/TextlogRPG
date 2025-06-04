#pragma once
#include "../Util/EGameState.h"
#include <unordered_map>
#include <string>


using namespace std;

class GameManager 
{
public:
	GameManager(EGameState initialState, class Player* player, class Dungeon* dungeon);

	~GameManager();


private:
	EGameState gameState;
    class Player* playerPtr;
	class Dungeon* dungeonptr;
	unordered_map<EGameState, class Area*> mapList;
    
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

	void BattleInDungeonStage(vector<class Monster*> monsters, class DungeonStage* stage);
	

	void GameOverProcess();

	
};