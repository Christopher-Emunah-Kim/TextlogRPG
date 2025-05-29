#include "GameMode.h"

string GameMode::GetStateString() const
{
	switch (gameState) 
	{
		case EGameState::TITLE: return "타이틀"; break;
		case EGameState::VILLAGE: return "마을"; break;
		case EGameState::DUNGEON: return "던전"; break;
		case EGameState::BATTLE: return "전투"; break;
		case EGameState::GAME_OVER: return "게임 오버"; break;
		default: return "알 수 없음"; break;
	}
}
