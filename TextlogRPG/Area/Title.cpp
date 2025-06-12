#include "Title.h"
#include "../Character/Player.h"
#include "../Util/EGameState.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Enter(Player* player)
{
	RenderPlayerGreeting(player);
}

void Title::Initialize(Player* player)
{

}

EGameState Title::Process(Player* player)
{
	Enter(player);

	char menuChoice = Common::GetCharInput();

	return HandleChoice(menuChoice, player);
}

EGameState Title::HandleChoice(char menuChoice, Player* player)
{
	switch (menuChoice)
	{
	case '1':
	{
		return EGameState::VILLAGE;
	}
	break;
	case '2':
	{
		return EGameState::DUNGEON;
	}
	break;
	case '3':
	{
		if (player == nullptr)
		{
			Common::PrintErrorMsg("플레이어 정보가 없습니다.");
		}
		else
		{
			Common::PauseAndClearScreen();
			player->RenderPlayerStatus();
		}
		return EGameState::TITLE;
	}
	break;
	case '4':
	{
		return EGameState::GAME_OVER;
	}
	break;

	default:
	{
		Common::PrintErrorMsg("잘못된 입력입니다.");
		return EGameState::TITLE; 
	}
	break;
	}
}

void Title::RenderPlayerGreeting(Player* player)
{
	string strWelcomeMsg = "환영합니다, 용사 " + player->GetName() + " 님!\n이제 당신의 모험이 시작됩니다!!";

	Common::PrintSystemMsg(strWelcomeMsg);

	Common::PrintSystemMsg("타이틀을 출력중입니다...");

	Common::PauseAndClearScreen(2500);

	Common::PrintSystemMsg("타이틀 화면입니다.\n\n1. 마을로 가기\n\n2. 던전에 가기\n\n3. 플레이어 정보 확인하기 \n\n4. 게임을 떠나기");
}

