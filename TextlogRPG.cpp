#include "TextlogRPG/Util/Common.h"
#include "TextlogRPG/Util/EGameState.h"
#include "TextlogRPG/Core/GameManager.h"
#include "TextlogRPG/Character/Player.h"
#include "TextlogRPG/Area/Dungeon.h"

using namespace std;


int main()
{
	//Game Start Settings
	Player* player = Player::CreateCharacter("NONE");
	EGameState initialState = EGameState::TITLE;
	Dungeon* dungeon = nullptr;

	GameManager gameManager(initialState, player, dungeon);
	
	gameManager.Run();

	return 0;

}
