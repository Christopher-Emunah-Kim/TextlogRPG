#pragma once
#include "../Core/GameMode.h"
#include "../Character/Player.h"
#include "../Area/Area.h"

class GameManager 
{
private:
    GameMode gameMode;
    Player* playerPtr;
	Area* currentAreaPtr;
    
public:
	GameManager(const GameMode& gm, Player* player)
		: gameMode(GameMode(gm.GetGameState())), playerPtr(player), currentAreaPtr(nullptr)
	{	}
        
	~GameManager();

	//Main Process of Game
	void InitializeGame();
	void RunProcessTitle();
	void RunProcessVillage();
	void RunProcessHealer(class Healer* healer);
	void RunProcessMerchant(class Merchant* merchant);
	void RunProcessDungeon();
	void RunProcessCombat();
	
    void Run();
};