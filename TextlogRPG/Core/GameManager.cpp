#include "GameManager.h"
#include <ctime>

#include "../Util/EGameState.h"
#include "../Util/Common.h"

#include "../Character/Player.h"
#include "../Character/Monster.h"
#include "../Character/CharacterInfo.h"
#include "../NPC/Healer.h"
#include "../NPC/Merchant.h"

#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "../Core/ItemManager.h"

#include "../Area/Area.h"
#include "../Area/Title.h"
#include "../Area/Village.h"
#include "../Area/Dungeon.h"
#include "../Area/DungeonStage.h"
#include "../Util/Dialogue.h"

GameManager::GameManager(EGameState initialState, Player* player, Dungeon* dungeon)
	: m_gameState(initialState), m_playerPtr(player), m_dungeonptr(dungeon)
{
	//manage dynamic memory allocation for maps
	m_sceneAreaMap.insert(make_pair(EGameState::TITLE, new Title()));
	m_sceneAreaMap.insert(make_pair(EGameState::VILLAGE, new Village()));
	m_sceneAreaMap.insert(make_pair(EGameState::DUNGEON, new Dungeon()));
	
	//initialize items on game
	ItemManager::GetInstance().InitializeItems();

	if (m_playerPtr == nullptr)
	{
		m_playerPtr = Player::CreateCharacter();
	}
	else
	{
		m_playerPtr->SetName("DefaultPlayer");
	}
}

GameManager::~GameManager()
{
	if (m_playerPtr) 
	{
		delete m_playerPtr;
		m_playerPtr = nullptr; 
	}
	if (m_dungeonptr)
	{
		delete m_dungeonptr;
		m_dungeonptr = nullptr;
	}
	for (unordered_map<EGameState, Area*>::iterator i = m_sceneAreaMap.begin(); i != m_sceneAreaMap.end(); ++i)
	{
		pair<EGameState, Area*> map = *i;
		if (map.second)
			delete map.second;
	}
	m_sceneAreaMap.clear();
}


void GameManager::Run() 
{
    InitializeGame();

	EGameState CurrentGameState = GetGameState();

	//LOOP TIME CHECK
	clock_t lastFrameTime = clock();
	clock_t currentTime;
	float deltaTime;

	while (CurrentGameState != EGameState::GAME_OVER)
	{
		//Calculate deltaTime
		//CLOCKS_PER_SEC : 초당 clock tick의 수 매크로
		//clock() : 프로세서가 소비한 시간 반환 함수
		//clock_t : clock ticks 자료형.
		currentTime = clock();
		deltaTime = static_cast<float>(currentTime - lastFrameTime) / CLOCKS_PER_SEC;
		lastFrameTime = currentTime;

		switch (m_gameState)
		{
		case EGameState::TITLE:
		{
			RunProcessTitle(deltaTime);
		}
			break;
		case EGameState::VILLAGE:
		{
			RunProcessVillage(deltaTime);
		}
			break;
		case EGameState::DUNGEON:
		{
			RunProcessDungeon(deltaTime);
		}
			break;

		default:
		{
			SetGameState(EGameState::GAME_OVER);
		}
			break;
		}

		if (m_playerPtr)
		{
			m_playerPtr->Update();
		}

		CurrentGameState = GetGameState();
	}
}

void GameManager::InitializeGame() 
{
	RenderWelcomMsg();

	Common::PauseAndClearScreen();

	RequestPlayerName();

	SetGameState(EGameState::TITLE);
}


#pragma region InitializeGame methods
void GameManager::RenderWelcomMsg()
{
	/*vector<Dialogue> initialDialogs;
	initialDialogs.push_back(Dialogue::NewText(0, "[Unknown] 안녕하신가 용사여\n[Unknown] 놀라지 말게. 자네의 3D세상은 멀쩡하다네"));
	initialDialogs.push_back(Dialogue::NewText(1, "[Unknown] 다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가?\n[Unknown] 그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세."));
	initialDialogs.push_back(Dialogue::NewText(2, "[Unknown] 자, 이제 게임을 시작하지\n[Unknown] 준비가 되었는가?"));
	Dialogue::ShowDialogs(initialDialogs);*/

	Common::PrintSystemMsg("\n\n[Unknown] 안녕하신가 용사여\n\n[Unknown] 놀라지 말게. 자네의 3D세상은 멀쩡하다네");
	Common::PauseAndClearScreen(3000);
	Common::PrintSystemMsg("\n\n[Unknown] 다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가?\n\n[Unknown] 그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세.");
	Common::PauseAndClearScreen(3000);
	Common::PrintSystemMsg("\n\n[Unknown] 자, 이제 게임을 시작하지\n\n[Unknown] 준비가 되었는가?");
	Common::PauseAndClearScreen(3000);
}
void GameManager::RequestPlayerName()
{
	Common::ShowOption("[System] 이해할 수 없는 곳이다. \n\n당신의 선택은?\n\n1. 게임을 시작한다.\n\n2. 당장 도망친다.");

	char titleChoice = Common::GetCharInput();

	if (titleChoice == '1')
	{
		Common::PrintSystemMsg("도망치려 했지만, 이미 늦었다.\n\n게임을 시작할 수 밖에.");
		Common::PauseAndClearScreen(2000);
	}
	else
	{
		Common::PrintSystemMsg("당신은 도망칠 수 없습니다. 강제로 게임을 시작합니다..");
		Common::PauseAndClearScreen(2000);
	}
	
	string inputName;
	while (true)
	{
		Common::PrintSystemMsg("당신의 이름을 입력하시오. \n\n이름은 20자 이내로 입력해주세요.");
		inputName = InputManager::GetInstance().GetLineInput();

		// 공백이 포함되어 있으면 에러 메시지 출력
		if (any_of(inputName.begin(), inputName.end(), ::isspace))
		{
			Common::PrintErrorMsg("이름에 공백이 포함될 수 없습니다. 다시 입력해주세요.");
			continue;
		}

		if (inputName.empty())
		{
			Common::PrintErrorMsg("이름을 입력해주세요.");
			continue;
		}

		if (inputName.length() > DEFAULT_NAMING_LENGTH)
		{
			inputName = inputName.substr(0, DEFAULT_NAMING_LENGTH);
		}
		break;
	}
	
	m_playerPtr->SetName(inputName);
}
#pragma endregion


void GameManager::RunProcessTitle(float deltaTime)
{
	Title* pTitleArea = dynamic_cast<Title*>(m_sceneAreaMap[EGameState::TITLE]);

	if (pTitleArea)
	{
		pTitleArea->Initialize(m_playerPtr);

		EGameState nextState = pTitleArea->Run(m_playerPtr);

		SetGameState(nextState);
	}
}



void GameManager::RunProcessVillage(float deltaTime)
{
	Village* pVilalgeArea = dynamic_cast<Village*>(m_sceneAreaMap[EGameState::VILLAGE]);
	if (pVilalgeArea)
	{
		pVilalgeArea->Initialize(m_playerPtr);

		EGameState nextState = pVilalgeArea->Run(m_playerPtr);

		SetGameState(nextState);
	}
}



void GameManager::RunProcessDungeon(float deltaTime)
{
	Dungeon* pDungeonArea = dynamic_cast<Dungeon*>(m_sceneAreaMap[EGameState::DUNGEON]);
	if (pDungeonArea)
	{
		pDungeonArea->Initialize(m_playerPtr);

		EGameState nextState = pDungeonArea->Run(m_playerPtr);

		Common::PauseAndClearScreen();

		SetGameState(nextState);
	}
}


