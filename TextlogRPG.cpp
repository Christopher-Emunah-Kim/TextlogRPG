#include "TextlogRPG/Util/Common.h"
#include "TextlogRPG/Util/EGameState.h"
#include "TextlogRPG/Core/GameManager.h"
#include "TextlogRPG/Character/Player.h"
#include "TextlogRPG/Area/Dungeon.h"

using namespace std;


int32 main()
{
	// 로케일 설정-한글출력지원
	locale::global(locale("kor"));
	wcin.imbue(locale());
	wcout.imbue(locale());

	//Game Start Settings
	Player* player = Player::CreateCharacter("NONE");
	EGameState initialState = EGameState::TITLE;
	Dungeon* dungeon = nullptr;

	GameManager gameManager(initialState, player, dungeon);
	
	gameManager.Run();

	return 0;

}
