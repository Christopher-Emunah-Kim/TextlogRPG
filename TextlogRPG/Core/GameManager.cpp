#include "GameManager.h"
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
	: gameState(initialState), playerPtr(player), dungeonptr(dungeon)
{
	//manage dynamic memory allocation for maps
	gameAreaMap.insert(make_pair(EGameState::TITLE, new Title()));
	gameAreaMap.insert(make_pair(EGameState::VILLAGE, new Village()));
	gameAreaMap.insert(make_pair(EGameState::DUNGEON, new Dungeon()));
	
	//initialize items on game
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
	for (unordered_map<EGameState, Area*>::iterator i = gameAreaMap.begin(); i != gameAreaMap.end(); ++i)
	{
		pair<EGameState, Area*> map = *i;
		if (map.second)
			delete map.second;
	}
	gameAreaMap.clear();
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
	ShowWelcomMsg();

	Common::PauseAndClearScreen();

	RequestPlayerName();

	SetGameState(EGameState::TITLE);
}


#pragma region InitializeGame methods
void GameManager::ShowWelcomMsg()
{
	vector<Dialogue> initialDialogs;
	initialDialogs.push_back(Dialogue::NewText(0, "[Unknown] 안녕하신가 용사여\n[Unknown] 놀라지 말게. 자네의 3D세상은 멀쩡하다네"));
	initialDialogs.push_back(Dialogue::NewText(1, "[Unknown] 다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가?\n[Unknown] 그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세."));
	initialDialogs.push_back(Dialogue::NewText(2, "[Unknown] 자, 이제 게임을 시작하지\n[Unknown] 준비가 되었는가?"));
	Dialogue::ShowDialogs(initialDialogs);
}
void GameManager::RequestPlayerName()
{
	Common::ShowOption("[System] 이해할 수 없는 곳이다. \n 당신의 선택은?\n1. 게임을 시작한다.\n2. 당장 도망친다.");

	char titleChoice = Common::GetCharInput();

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
	
	playerPtr->SetName(inputName);
}
#pragma endregion

void GameManager::InitializeDungeon()
{
	//Generate Monster Lists(info)
	//FCharacterInfo(stats, maxHp, hp, lvl, name), dropExperience(exp), dropGold(gold)
	vector<FMonsterInfo> stage1 = {
		FMonsterInfo(CharacterStatus::NewStatus(6, 3, 6), 18, 18, 2, "허약한 고블린", 20, 10),
		FMonsterInfo(CharacterStatus::NewStatus(5, 4, 5), 20, 20, 2, "허약한 슬라임", 22, 12),
		FMonsterInfo(CharacterStatus::NewStatus(7, 4, 7), 22, 22, 3, "허약한 스켈레톤", 28, 15),
	};
	vector<FMonsterInfo> stage2 = {
		FMonsterInfo(CharacterStatus::NewStatus(12, 7, 10), 35, 35, 5, "허약한 오크", 40, 25),
		FMonsterInfo(CharacterStatus::NewStatus(15, 8, 12), 40, 40, 6, "허약한 드래곤", 60, 40),
		FMonsterInfo(CharacterStatus::NewStatus(16, 9, 11), 38, 38, 5, "강력한 고블린", 45, 30),
		FMonsterInfo(CharacterStatus::NewStatus(15, 8, 10), 39, 39, 5, "강력한 슬라임", 45, 30),
	};
	vector<FMonsterInfo> stage3 = {
		FMonsterInfo(CharacterStatus::NewStatus(22, 13, 15), 60, 60, 8, "강력한 스켈레톤", 80, 50),
		FMonsterInfo(CharacterStatus::NewStatus(25, 15, 16), 70, 70, 9, "강력한 오크", 90, 60),
		FMonsterInfo(CharacterStatus::NewStatus(28, 16, 18), 80, 80, 10, "완전 강력한 스켈레톤", 120, 80),
		FMonsterInfo(CharacterStatus::NewStatus(32, 18, 20), 90, 90, 12, "완전 강력한 고블린", 150, 100),
		FMonsterInfo(CharacterStatus::NewStatus(36, 20, 22), 100, 100, 13, "완전 강력한 슬라임", 180, 120),
		FMonsterInfo(CharacterStatus::NewStatus(40, 22, 25), 110, 110, 15, "완전 강력한 드래곤", 250, 180),
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
	Area* ptrTitleArea = gameAreaMap[EGameState::TITLE];
	if (ptrTitleArea)
	{
		ptrTitleArea->Enter(playerPtr);
	}
	
	char menuChoice = Common::GetCharInput();
	
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
	Village* pVilalgeArea = dynamic_cast<Village*>(gameAreaMap[EGameState::VILLAGE]);

	Healer* healer = new Healer("앤더슨", DEFAULT_HEAL_COST);
    Merchant* merchant = new Merchant("토니");
	
	pVilalgeArea->AddNPC(healer);
	pVilalgeArea->AddNPC(merchant);
	
	ItemManager& itemManager = ItemManager::GetInstance();
	vector<string> items = itemManager.GetItemList();

	for (size_t i = 0; i <  items.size(); ++i)
	{
		const string& itemName = items[i];
		Item* item = itemManager.GetItem(itemName);
		if (item == nullptr)
			continue;
		
		EItemType itemType = item->GetItemInfo().itemType;
		int32 itemPrice = item->GetItemInfo().itemCost;

		if (itemType == EItemType::WEAPON || itemType == EItemType::ARMOR || itemType == EItemType::MISC)
		{
			merchant->AddItemForSale(itemName, itemPrice);
		}
	}


	
	pVilalgeArea->Enter(playerPtr);

	char villageChoice = Common::GetCharInput();

	Common::PauseAndClearScreen();

	switch (villageChoice)
	{
		case '1':
		{
			pVilalgeArea->InteractWithNPC(playerPtr, healer);
			SetGameState(EGameState::VILLAGE);

			break;
		}
		case '2':
		{
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
	if (dungeonptr == nullptr)
	{
		InitializeDungeon();
	}
	else
	{
		Common::PrintSystemMsg("당신을 위한 던전 스테이지가 준비되어 있습니다.");
	}

	if (playerPtr == nullptr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. 던전 탐험을 시작할 수 없습니다.");
		return;
	}

	dungeonptr->Enter(playerPtr);

	char dungeonChoice = Common::GetCharInput();

	Common::PauseAndClearScreen();

	switch (dungeonChoice)
	{
	case '1': // Choose Battle
	{
		while (true)
		{
			 DungeonStage* stage = dungeonptr->GetCurrentStage();
			if (stage == nullptr)
			{
				Common::PrintSystemMsg("유효한 던전 스테이지가 존재하지 않습니다.\n마을로 돌아갑니다.");
				SetGameState(EGameState::VILLAGE);
				return;
			}

			vector<Monster*> stageMonsterList = stage->GetMonsters();
			if (stageMonsterList.empty())
			{
				stage->EnterStage();
				stageMonsterList = stage->GetMonsters();
			}

			while (true)
			{
				// Check the Monsters on stage all dead
				bool allMonstersDead = true;
				for (size_t i = 0; i <stageMonsterList.size(); ++i)
				{
					Monster* mon = stageMonsterList[i];
					if (mon->GetCharacterInfo().iCurrentHealth > 0)
					{
						allMonstersDead = false;
						break;
					}
				}

				if (allMonstersDead)
				{
					if (dungeonptr->IsMoreStageLeft())
					{
						Common::PrintSystemMsg("다음 스테이지로 진입합니다");
						Common::PauseAndClearScreen();
						stage = dungeonptr->GetCurrentStage();
						stage->EnterStage();
						stageMonsterList = stage->GetMonsters();
						continue;
					}
					else
					{
						Common::PrintSystemMsg("모든 던전 스테이지를 클리어했습니다.\n마을로 돌아갑니다..");
						Common::PauseAndClearScreen();
						SetGameState(EGameState::VILLAGE);
						return;
					}
				}

				
				Common::PrintSystemMsg("정말 이 스테이지를 도전하시겠습니까?\n\n1. 멈출 수 없다. 앞으로 나아가자.\n\n2. 목숨은 소중하니까, 도망간다(마을로 복귀)");
				char stageChoice = Common::GetCharInput();

				Common::PauseAndClearScreen();

				if (stageChoice == '2') {
					Common::PrintSystemMsg("던전에서 도망쳤습니다. 마을로 돌아갑니다.");
					Common::PauseAndClearScreen();
					SetGameState(EGameState::VILLAGE);
					return;
				}

				// Battle with monster
				BattleInDungeonStage(stageMonsterList, stage);

				// exception_RUN/DEAD_quit the loop
				if (GetGameState() == EGameState::VILLAGE || GetGameState() == EGameState::GAME_OVER)
					return;
			}

		}
		break;
	}
	case '2': // Choose RUN
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

void GameManager::BattleInDungeonStage(const vector<Monster*>& monsters, DungeonStage* stage)
{
	// 랜덤 시드 설정 (프로그램 전체에서 한 번만 호출하는 것이 더 좋음)
	srand(static_cast<unsigned int>(time(NULL)));

	while (true)
	{
		// 살아있는 몬스터만 추출
		vector<Monster*> aliveMonsters;
		for (size_t i = 0; i < monsters.size(); ++i)
		{
			Monster* mon = monsters[i];
			if (mon->GetCharacterInfo().iCurrentHealth > 0)
				aliveMonsters.push_back(mon);
		}

		// 모두 죽었으면 종료
		if (aliveMonsters.empty())
			break;

		// 랜덤 인덱스 선택
		size_t randomIndex = rand() % aliveMonsters.size();
		Monster* randomMonster = aliveMonsters[randomIndex];

		// 전투 시작
		EBattleResult result = dungeonptr->EncounterMonster(playerPtr, randomMonster);

		switch (result)
		{
		case EBattleResult::PLAYER_DEAD:
			GameOverProcess();
			return;
		case EBattleResult::PLAYER_RUN:
			SetGameState(EGameState::VILLAGE);
			return;
		case EBattleResult::PLAYER_WIN:
			stage->OnMonsterDefeat(randomMonster);
			// 경험치, 골드 등 보상 지급 로직 추가 가능
			break;
		default:
			Common::PrintErrorMsg("전투 중 알 수 없는 오류가 발생했습니다.");
			return;
		}
	}

}


void GameManager::GameOverProcess()
{
	//TODO : 던전에서 죽었을때 마을로 돌아가는것이 아니라 종료되는문제 해결
	Common::PrintSystemMsg("게임이 종료되었습니다.\n다시 시작하려면 게임을 재실행해주세요.");
	Common::PauseAndClearScreen();
	SetGameState(EGameState::GAME_OVER);
}

