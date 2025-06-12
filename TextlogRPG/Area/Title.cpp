#include "Title.h"
#include "../Character/Player.h"

void Title::Enter(Player* player)
{
	string strWelcomeMsg = "환영합니다, 용사 " + player->GetName() + " 님!\n이제 당신의 모험이 시작됩니다!!";

	Common::PrintSystemMsg(strWelcomeMsg);

	Common::PrintSystemMsg("타이틀을 출력중입니다...");

	Common::PauseAndClearScreen(2500);

	Common::PrintSystemMsg("타이틀 화면입니다.\n\n1. 마을로 가기\n\n2. 던전에 가기\n\n3. 플레이어 정보 확인하기 \n\n4. 게임을 떠나기");
}

