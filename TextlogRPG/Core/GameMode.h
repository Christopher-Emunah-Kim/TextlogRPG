#pragma once
#include "../Util/Common.h"


enum class EGameState
{
	NONE,
	TITLE,
	VILLAGE,
	DUNGEON,
	BATTLE,
	GAME_OVER
};

class GameMode
{
	EGameState gameState;

public:
	GameMode(EGameState gs) : gameState(gs) {}

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


