#include "GameManager.h"
#include "../Util/EGameState.h"
#include "../Util/Common.h"
#include "../Util/Option.h"
#include "../Util/Dialog.h"

#include "../Character/Player.h"
#include "../Character/Monster.h"
#include "../Character/CharacterInfo.h"
#include "../NPC/Healer.h"
#include "../NPC/Merchant.h"

#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "../Item/ItemManager.h"

#include "../Area/Area.h"
#include "../Area/Title.h"
#include "../Area/Village.h"
#include "../Area/Dungeon.h"
#include "../Area/DungeonStage.h"
#include "../Util/Dialogue.h"


GameManager::GameManager(EGameState initialState, Player* player, Dungeon* dungeon)
	: gameState(initialState), playerPtr(player), dungeonptr(dungeon)
{
	//manage dynamic memory allocation for maps
	mapList.insert(make_pair(EGameState::TITLE, new Title()));
	mapList.insert(make_pair(EGameState::VILLAGE, new Village()));
	mapList.insert(make_pair(EGameState::DUNGEON, new Dungeon()));
	
	ItemManager::GetInstance().InitializeItems();

	if (playerPtr == nullptr)
	{
		playerPtr = Player::CreateCharacter("DefaultPlayer");
	}
	else
	{
		playerPtr->SetName("DefaultPlayer");
	}
}

GameManager::~GameManager()
{
	if (playerPtr) 
	{
		delete playerPtr;
		playerPtr = nullptr; 
	}
	if (dungeonptr)
	{
		delete dungeonptr;
		dungeonptr = nullptr;
	}
	for (const pair<EGameState, Area*>& map : mapList)
	{
		if(map.second)
		delete map.second; 
	}
	mapList.clear();
}


void GameManager::Run() 
{
    InitializeGame();

	EGameState CurrentGameState = GetGameState();

	while (CurrentGameState != EGameState::GAME_OVER)
	{
		switch (gameState)
		{
		case EGameState::TITLE:
			RunProcessTitle();
			break;
		case EGameState::VILLAGE:
			RunProcessVillage();
			break;
		case EGameState::DUNGEON:
			RunProcessDungeon();
			break;

		default:
			SetGameState(EGameState::GAME_OVER);
			break;
		}
	}
}

void GameManager::InitializeGame() 
{
	WelcomMsg();

	Common::PauseAndClearScreen();

	SetPlayerName();

	SetGameState(EGameState::TITLE);
}


#pragma region InitializeGame methods
void GameManager::WelcomMsg()
{
	vector<Dialogue> initialDialogs;
	initialDialogs.push_back(Dialogue::NewText(0, "[Unknown] 안녕하신가 용사여\n[Unknown] 놀라지 말게. 자네의 3D세상은 멀쩡하다네"));
	initialDialogs.push_back(Dialogue::NewText(1, "[Unknown] 다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가?\n[Unknown] 그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세."));
	initialDialogs.push_back(Dialogue::NewText(2, "[Unknown] 자, 이제 게임을 시작하지\n[Unknown] 준비가 되었는가?"));
	Dialogue::ShowDialogs(initialDialogs);
}
void GameManager::SetPlayerName()
{
	Dialogue::ShowOption("[System] 이해할 수 없는 곳이다. \n 당신의 선택은?\n1. 게임을 시작한다.\n2. 당장 도망친다.");

	char titleChoice;
	cin >> titleChoice;
	cin.ignore(1024, '\n');

	if (titleChoice == '1')
	{
		Common::PrintSystemMsg("도망치려 했지만, 이미 늦었다.\n\n게임을 시작할 수 밖에.");
		Common::PauseAndClearScreen();
	}
	else
	{
		Common::PrintSystemMsg("당신은 도망칠 수 없습니다. 강제로 게임을 시작합니다..");
		Common::PauseAndClearScreen();
	}
	
	string inputName;
	while (true)
	{
		Common::PrintSystemMsg("당신의 이름을 입력하시오. \n이름은 20자 이내로 입력해주세요.");
		getline(cin, inputName);

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

		if (inputName.length() > 20)
		{
			inputName = inputName.substr(0, 20);
		}
		break;
	}
	
	playerPtr->SetName(inputName);
}
#pragma endregion

void GameManager::InitializeDungeon()
{
	//Generate Monster Lists(info)
	//FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold)
	vector<FMonsterInfo> stage1 = {
		FMonsterInfo(CharacterStatus::NewStatus(5, 3, 5), 10, 10, 1, "평범한 고블린", 15, 8),
		FMonsterInfo(CharacterStatus::NewStatus(6, 4, 8), 12, 12, 4, "평범한 스켈레톤", 25, 15),
		FMonsterInfo(CharacterStatus::NewStatus(8, 5, 10), 15, 15, 3, "평범한 오크", 30, 20),
		FMonsterInfo(CharacterStatus::NewStatus(12, 8, 15), 20, 20, 5, "평범한 드래곤", 50, 30)
	};
	vector<FMonsterInfo> stage2 = {
		FMonsterInfo(CharacterStatus::NewStatus(5, 3, 5), 10, 10, 1, "평범한 고블린", 15, 8),
		FMonsterInfo(CharacterStatus::NewStatus(6, 4, 8), 12, 12, 4, "평범한 스켈레톤", 25, 15),
		FMonsterInfo(CharacterStatus::NewStatus(8, 5, 10), 15, 15, 3, "평범한 오크", 30, 20),
		FMonsterInfo(CharacterStatus::NewStatus(12, 8, 15), 20, 20, 5, "평범한 드래곤", 50, 30)
	};
    vector<FMonsterInfo> stage3 = {
		FMonsterInfo(CharacterStatus::NewStatus(5, 3, 5), 10, 10, 1, "강력한 고블린", 15, 8),
		FMonsterInfo(CharacterStatus::NewStatus(4, 2, 1), 8, 8, 2, "강력한 슬라임", 15, 5),
		FMonsterInfo(CharacterStatus::NewStatus(6, 4, 8), 12, 12, 4, "강력한 스켈레톤", 25, 15),
		FMonsterInfo(CharacterStatus::NewStatus(8, 5, 10), 15, 15, 3, "강력한 오크", 30, 20),
		FMonsterInfo(CharacterStatus::NewStatus(12, 8, 15), 20, 20, 5, "강력한 드래곤", 50, 30)
	};
	
	vector<vector<FMonsterInfo>> dungeonStages = { stage1, stage2, stage3 };


	//Generate new Dungeon
	if (dungeonptr)
	{
		delete dungeonptr;
		dungeonptr = nullptr;
	}
	dungeonptr = new Dungeon(dungeonStages);

}

void GameManager::RunProcessTitle() 
{
	Area* ptrTitleArea = mapList[EGameState::TITLE];
	if (ptrTitleArea)
	{
		ptrTitleArea->Enter(playerPtr);
	}
	
	char menuChoice;
	cin >> menuChoice;
	cin.ignore(1024, '\n');
	
	switch (menuChoice)
	{
		case '1': 
		{
			SetGameState(EGameState::VILLAGE);
		}
			break;
		case '2': 
		{
			SetGameState(EGameState::DUNGEON); 
		}
			break;
		case '3':
		{
			if (!playerPtr) {
				Common::PrintErrorMsg("플레이어 정보가 없습니다.");
				return;
			}
			Common::PauseAndClearScreen();
			playerPtr->ShowPlayerStatus();
			SetGameState(EGameState::TITLE);
		}
			break;
		case '4': 
		{
			SetGameState(EGameState::GAME_OVER); 
		}
			break;

		default:
		{
			Common::PrintErrorMsg("잘못된 입력입니다.");
		}
			break;
	}
	Common::PauseAndClearScreen();
}

void GameManager::RunProcessVillage()
{
	//Choice in Village
	Village* pVilalgeArea = static_cast<Village*>(mapList[EGameState::VILLAGE]);

	Healer* healer = new Healer("앤더슨", 15);
    Merchant* merchant = new Merchant("토니");
	
	pVilalgeArea->AddNPC(healer);
	pVilalgeArea->AddNPC(merchant);
	
	//TODO : 아이템 리스트 정보를 csv에서 불러와 배열 push해주는 메서드 추가
	//TODO : 반복되는기능 함수로 묶기
	merchant->AddItemForSale("초보자의 검", 50);
	merchant->AddItemForSale("철검", 80);
	merchant->AddItemForSale("초보자의 갑옷", 60);
	merchant->AddItemForSale("가죽갑옷", 100);

	
	pVilalgeArea->Enter(playerPtr);

	char villageChoice;
	cin >> villageChoice;
	cin.ignore(1024, '\n');

	Common::PauseAndClearScreen();

	switch (villageChoice)
	{
		case '1':
		{
			//village->InteractWithNPC(playerPtr, healer);
			pVilalgeArea->InteractWithNPC(playerPtr, healer);
			SetGameState(EGameState::VILLAGE);

			break;
		}
		case '2':
		{
			//village->InteractWithNPC(playerPtr, merchant);
			pVilalgeArea->InteractWithNPC(playerPtr, merchant);
			SetGameState(EGameState::VILLAGE);

			break;
		}
		case '3':
		{
			SetGameState(EGameState::TITLE); break;
		}

		default: 
			Common::PrintErrorMsg("잘못된 입력입니다.");
	}
	Common::PauseAndClearScreen();

	delete healer;
	delete merchant;
	healer = nullptr;
	merchant = nullptr;
}

void GameManager::RunProcessDungeon()
{
	if (!dungeonptr)
	{
		InitializeDungeon();
	}
	else
	{
		Common::PrintSystemMsg("당신을 위한 던전 스테이지가 준비되어 있습니다.");
	}

	if (!playerPtr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. 던전 탐험을 시작할 수 없습니다.");
		return;
	}

	dungeonptr->Enter(playerPtr);

	//Dungeon Settings
	DungeonStage* stage = dungeonptr->GetCurrentStage();

	if (stage) 
	{
		stage->EnterStage();
	}
	else
	{
		Common::PrintSystemMsg("유효한 던전 스테이지가 존재하지 않습니다.\n마을로 돌아갑니다.");
		SetGameState(EGameState::VILLAGE);
		return;
	}


	vector<Monster*> monsters = stage->GetMonsters();

	char dungeonChoice;
	cin >> dungeonChoice;
	cin.ignore(1024, '\n');

	Common::PauseAndClearScreen();

	switch (dungeonChoice)
	{
		case '1': //ChooseBattle
		{
			BattleInDungeonStage(monsters, stage);
			break;
		}
		case '2': //ChooseRun
		{
			Common::PrintSystemMsg("무모한 도전이 반드시 정답은 아닙니다.\n던전 탐험을 중단하고 마을로 돌아갑니다.");
			Common::PauseAndClearScreen();
			SetGameState(EGameState::VILLAGE);
			break;
		}

		default:
		{
			Common::PrintErrorMsg("잘못된 입력입니다.");
			Common::PrintErrorMsg("던전에 재입장합니다..");
			Common::PauseAndClearScreen();
			SetGameState(EGameState::DUNGEON);
			break;
		}
	}
}

void GameManager::BattleInDungeonStage(vector<Monster*> monsters, DungeonStage* stage)
{
	vector<Monster*> aliveMonsters;
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		Monster* mon = monsters[i];
		if (mon->GetCharacterInfo().iCurrentHealth > 0)
			aliveMonsters.push_back(mon);
	}

	//Check if there are any monsters left in the dungeon
	if (aliveMonsters.empty()) {
		if (dungeonptr->NextStage()) {
			Common::PrintSystemMsg("다음 스테이지로 이동합니다.");
			Common::PauseAndClearScreen();
			RunProcessDungeon();
			return;
		}
		else {
			Common::PrintSystemMsg("모든 던전 스테이지를 클리어했습니다!\n마을로 돌아갑니다.");
			Common::PauseAndClearScreen();
			SetGameState(EGameState::VILLAGE);
			return;
		}
	}
	//Generate a random index 
	srand(static_cast<unsigned int>(time(NULL))); // 현재 시간을 시드로 사용
	size_t randomIndex = rand() % aliveMonsters.size();
	Monster* randomMonster = aliveMonsters[randomIndex];

	//Start Battle with the random monster
	bool isPlayerAlive = dungeonptr->EncounterMonster(playerPtr, randomMonster);
	Common::PauseAndClearScreen();

	if (isPlayerAlive == false)
	{
		GameOverProcess();
		return;
	}
	if (randomMonster->GetCharacterInfo().iCurrentHealth <= 0)
	{
		stage->OnMonsterDefeat(randomMonster);
	}
	SetGameState(EGameState::DUNGEON);
}



void GameManager::GameOverProcess()
{
	//TODO : 던전에서 죽었을때 마을로 돌아가는것이 아니라 종료되는문제 해결
	Common::PrintSystemMsg("게임이 종료되었습니다.\n다시 시작하려면 게임을 재실행해주세요.");
	Common::PauseAndClearScreen();
	SetGameState(EGameState::GAME_OVER);
}

