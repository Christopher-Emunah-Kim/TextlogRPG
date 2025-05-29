#pragma once
#include "../Core/GameMode.h"
#include "../Character/Player.h"
#include "../Area/Area.h"

class GameManager {
private:
    GameMode gameMode;
    Player* player;
	Area* currentArea;
    
    //Main Process of Game
    void InitializeGame();
    void RunProcessTitle();
    void RunProcessVillage();
    void RunProcessHealer();
    void RunProcessMerchant();
    void RunProcessDungeon();
	void RunProcessCombat();
    
public:
	GameManager(const GameMode& gm, Player* player);
        
	~GameManager();
	
    void Run();
};