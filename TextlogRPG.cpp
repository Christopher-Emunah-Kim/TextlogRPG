#include "TextlogRPG/Util/Common.h"
#include "TextlogRPG/Util/EGameState.h"
#include "TextlogRPG/Core/GameManager.h"
#include "TextlogRPG/Character/Player.h"

using namespace std;


int main()
{
	//Game Start Settings
	Player* player = Player::CreateCharacter("NONE");
	EGameState initialState = EGameState::TITLE;

	GameManager gameManager(initialState, player);
	
	gameManager.Run();

	return 0;

}
