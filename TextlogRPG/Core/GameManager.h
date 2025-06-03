#pragma once
#include "../Util/EGameState.h"
#include <unordered_map>
#include <string>


using namespace std;

class GameManager 
{
private:
	EGameState gameState;
    class Player* playerPtr;
	class Dungeon* dungeonptr;
	unordered_map<EGameState, class Area*> mapList;
    
public:
	GameManager(EGameState initialState, class Player* player, class Dungeon* dungeon);
        
	~GameManager();

	//Managing GameState
	void SetGameState(const EGameState& gs_in)	{ gameState = gs_in; }
	EGameState GetGameState() const 	{return gameState;	}
	//string GetStateString() const;

	//Dungeon-Stage-Monster Initialization
	void InitializeDungeon();

	//Main Process of Game
	void InitializeGame();
	void SetPlayerName();
	void WelcomMsg();
	void RunProcessTitle();
	void RunProcessVillage();
	void RunProcessDungeon();
	void GameOverProcess();
	
    void Run();
	void LoopByGameState();
};