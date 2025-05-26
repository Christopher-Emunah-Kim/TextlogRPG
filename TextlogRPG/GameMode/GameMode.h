#pragma once


	/*GameMode
	6.0 class GameMode 
	6.0.1 Enum class EGameState
	6.0.2 EGameState currentState
	6.0.3 EGameState& GetCurrentState() const
	6.0.4 void ChangeGameState(EGameState newState)
	6.0.5 void InitializeGame()
	Game states: TITLE, VILLAGE, DUNGEON */


enum class EGameState
{
	NONE,
	TITLE,
	VILLAGE,
	DUNGEON,
};

class GameMode
{
	EGameState gameState = EGameState::NONE;

public:
	GameMode() {}

	//SetGameState
	void SetGameState(const EGameState& gs_in)
	{
		gameState = gs_in;
	}
	//GetGameState
	EGameState& GetGameState()
	{
		return gameState;
	}


	~GameMode() {}
};

