#include "GameManager.h"
#include "../Dialog/Dialog.h"
#include "../Dialog/Option.h"


void GameManager::Run() {
    InitializeGame();
    while (gameMode.GetGameState() != EGameState::GAME_OVER) 
	{
        switch (gameMode.GetGameState()) 
		{
            case EGameState::TITLE: RunProcessTitle(); break;
            case EGameState::VILLAGE: RunProcessVillage(); break;
            case EGameState::HEALER: RunProcessHealer(); break;
            case EGameState::MERCHANT: RunProcessMerchant(); break;
            case EGameState::DUNGEON: RunProcessDungeon(); break;
            default: gameMode.SetGameState(EGameState::GAME_OVER); break;
        }
    }
}

void GameManager::InitializeGame() 
{
    // 플레이어 생성, 초기 상태 설정 등
   

	gameMode.SetGameState(EGameState::TITLE);
}

void GameManager::RunIntroSequence()
{
}

void GameManager::RunProcessTitle() 
{
    
}

void GameManager::RunProcessVillage()
{
}

void GameManager::RunProcessHealer()
{
}

void GameManager::RunProcessMerchant()
{
}

void GameManager::RunProcessDungeon()
{
}

void GameManager::RunProcessCombat()
{
}
