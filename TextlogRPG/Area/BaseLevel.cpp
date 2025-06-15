#include "BaseLevel.h"
#include <time.h>

EGameState BaseLevel::Run(Player* player, float deltaTime)
{
	Enter(player);

	m_isRunning = true;
	m_nextState = EGameState::TITLE; //default


	//GAME LOOP
	while (m_isRunning && ShouldExit()==false)
	{

		//LOOP
		ProcessInput(player);
		Update(deltaTime);
		Render();
	}

    return GetNextState();
}

