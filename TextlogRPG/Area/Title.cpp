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
	m_player = player;
	m_shouldShowMenu = true;
	m_shouldShowStatus = false;

	RenderPlayerGreeting(player);
	Render();
}

void Title::Initialize(Player* player)
{

}

EGameState Title::Process(Player* player)
{

	return Run(player);
}

void Title::ProcessInput(Player* player)
{
	if (m_shouldShowMenu)
	{
		m_input = Common::GetCharInput();
	}
}

void Title::Update(float deltaTime)
{
	m_accumulatedTime += deltaTime;

	if (m_input != 0)
	{
		switch (m_input)
		{
		case '1':
		{
			m_nextState = EGameState::VILLAGE;
			m_isRunning = false;
		}
		break;

		case '2':
		{
			m_nextState = EGameState::DUNGEON;
			m_isRunning = false;
		}
		break;

		case '3':
		{
			if (m_player != nullptr)
			{
				m_shouldShowMenu = false;
				m_shouldShowStatus = true;
				Common::PauseAndClearScreen();
				m_player->RenderPlayerStatus();

				m_accumulatedTime = 0.0f;
			}
			else
			{
				Common::PrintErrorMsg("플레이어 정보가 없습니다.");
			}
		}
		break;

		case '4':
		{
			m_nextState = EGameState::GAME_OVER;
			m_isRunning = false;
		}
		break;

		default:
		{
			Common::PrintErrorMsg("잘못된 입력입니다.");
		}
		break;
		}

		//초기화.
		m_input = 0;
		
	}

	if (m_shouldShowStatus && m_accumulatedTime > 1.0f)
	{
		m_shouldShowStatus = false;
		m_shouldShowMenu = true;
		m_accumulatedTime = 0.0f;
		Common::PauseAndClearScreen(1000);
		Render();
	}

}

void Title::Render()
{
	if (m_shouldShowMenu)
	{
		Common::PauseAndClearScreen();

		Common::PrintSystemMsg("타이틀 화면입니다.\n\n1. 마을로 가기\n\n2. 던전에 가기\n\n3. 플레이어 정보 확인하기 \n\n4. 게임을 떠나기");
	}
}

bool Title::ShouldExit()
{
	return !m_isRunning;
}

EGameState Title::GetNextState()
{
	return m_nextState;
}


void Title::RenderPlayerGreeting(Player* player)
{
	Common::PrintSystemMsg("환영합니다, 용사 " + player->GetName() + " 님!\n이제 당신의 모험이 시작됩니다!!");

	Common::PrintSystemMsg("타이틀을 출력중입니다...");

}

