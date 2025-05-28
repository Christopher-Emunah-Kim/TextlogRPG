#include "TextlogRPG/Util/Common.h"
#include "TextlogRPG/Core/GameManager.h"
#include "TextlogRPG/Character/Player.h"

using namespace std;


int main()
{
	//Game Start Settings
	GameMode gameMode(EGameState::TITLE);
	Player* player = Player::CreateCharacter("WM");

	GameManager gameManager(gameMode, player);
	
	gameManager.Run();


	return 0;

}
