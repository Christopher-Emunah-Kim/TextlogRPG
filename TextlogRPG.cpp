#include "TextlogRPG/Util/Common.h"
#include "TextlogRPG/Core/GameManager.h"
#include "TextlogRPG/Character/Player.h"

using namespace std;


int main()
{
	//Game Start Settings
	GameMode gameMode(EGameState::TITLE);
	FPlayerData playerData;
	Player player(playerData);

	GameManager gameManager(gameMode, player);
	
	gameManager.Run();


	return 0;

}
