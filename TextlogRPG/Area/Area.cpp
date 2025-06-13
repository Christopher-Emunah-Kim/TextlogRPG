#include "Area.h"
#include <time.h>

EGameState Area::Run(Player* player, float deltaTime)
{
	Enter(player);

	m_isRunning = true;
	m_nextState = EGameState::TITLE; //default

	/*clock_t lastTime = clock();
	float deltaTime;*/

	//GAME LOOP
	while (m_isRunning && ShouldExit()==false)
	{
		//update time
		/*clock_t currentTime = clock();
		deltaTime = static_cast<float>(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;*/

		//LOOP
		ProcessInput(player);
		Update(deltaTime);
		Render();
	}

    return GetNextState();
}

