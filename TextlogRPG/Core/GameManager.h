#pragma once
#include "../Core/GameMode.h"
#include <unordered_map>

class Player;
class Area;

class GameManager 
{
private:
    GameMode gameMode;
    Player* playerPtr;
	unordered_map<EGameState, class Area*> maps;
    
public:
	GameManager(const GameMode& gm, Player* player);
        
	~GameManager();

	//Main Process of Game
	void InitializeGame();
	void RunProcessTitle();
	void RunProcessVillage();
	void RunProcessDungeon();
	void GameOverProcess();
	
    void Run();
};