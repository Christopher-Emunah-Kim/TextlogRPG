#pragma once
#include "../Util/EGameState.h"
#include <unordered_map>
#include <string>

class Player;
class Area;

using namespace std;

class GameManager 
{
private:
	EGameState gameState;
    Player* playerPtr;
	std::unordered_map<EGameState, class Area*> mapList;
    
public:
	GameManager(EGameState initialState, Player* player);
        
	~GameManager();

	//Managing GameState
	void SetGameState(const EGameState& gs_in)	{ gameState = gs_in; }
	EGameState GetGameState() const 	{return gameState;	}
	std::string GetStateString() const;

	//Main Process of Game
	void InitializeGame();
	void RunProcessTitle();
	void RunProcessVillage();
	void RunProcessDungeon();
	void GameOverProcess();
	
    void Run();
};