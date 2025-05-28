#pragma once
#include "../Core/GameMode.h"
#include "../Character/Player.h"

class GameManager {
private:
    GameMode gameMode;
    Player* player;
    
    //Main Process of Game
    void InitializeGame();
    void RunIntroSequence();
    void RunProcessTitle();
    void RunProcessVillage();
    void RunProcessHealer();
    void RunProcessMerchant();
    void RunProcessDungeon();
	void RunProcessCombat();
    
public:
    GameManager(const GameMode& gm, const Player& player) 
        : gameMode(GameMode(gm.GetGameState())), player(new Player(player)) { }
	~GameManager() { if (player) delete player; }
    
    void Run();
};