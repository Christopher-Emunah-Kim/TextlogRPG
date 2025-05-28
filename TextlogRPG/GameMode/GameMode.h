#pragma once
#include "../Util/Common.h"


enum class EGameState
{
	NONE,
	TITLE,
	VILLAGE,
	DUNGEON,
	HEALER,
	MERCHANT,
	BATTLE,
	GAME_OVER
};

class GameMode
{
	EGameState gameState;

public:
	GameMode() {}

	//SetGameState
	void SetGameState(const EGameState& gs_in)
	{
		gameState = gs_in;
	}
	//GetGameState
	EGameState GetGameState() const
	{
		return gameState;
	}

	string GetStateString() const;



	~GameMode() {}
};



/*GameMode
6.0 class GameMode
6.0.1 Enum class EGameState
6.0.2 EGameState currentState
6.0.3 EGameState& GetCurrentState() const
6.0.4 void ChangeGameState(EGameState newState)
6.0.5 void InitializeGame()
Game states: TITLE, VILLAGE, DUNGEON */
