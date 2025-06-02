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
#include "../Item/ItemManager.h"

#include "../Area/Area.h"
#include "../Area/Title.h"
#include "../Area/Village.h"
#include "../Area/Dungeon.h"


GameManager::GameManager(EGameState initialState, Player* player, Dungeon* dungeon)
	: gameState(initialState), playerPtr(player), dungeonptr(dungeon ? dungeon : nullptr)
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

void GameManager::Run() 
{
    InitializeGame();

    while (GetGameState() != EGameState::GAME_OVER) 
	{
        switch ( GetGameState() )
		{
            case EGameState::TITLE: RunProcessTitle(); break;
            case EGameState::VILLAGE: RunProcessVillage(); break;
            case EGameState::DUNGEON: RunProcessDungeon(); break;
            default: SetGameState(EGameState::GAME_OVER); break;
        }
    }
}

string GameManager::GetStateString() const
{
	switch (gameState)
	{
	case EGameState::TITLE: return "타이틀"; break;
	case EGameState::VILLAGE: return "마을"; break;
	case EGameState::DUNGEON: return "던전"; break;
	case EGameState::GAME_OVER: return "게임 오버"; break;
	default: return "알 수 없음"; break;
	}
}

void GameManager::InitializeDungeon()
{
	//Generate Monster Lists(info)
	vector<FMonsterInfo> stage1 = {
		FMonsterInfo(CharacterStatus::NewStatus(4, 2, 1), 8, 8, 2, "슬라임", 15, 5)
	};
	vector<FMonsterInfo> stage2 = {
		FMonsterInfo(CharacterStatus::NewStatus(5, 3, 5), 10, 10, 1, "고블린", 15, 8)
	};
    vector<FMonsterInfo> stage3 = {
		FMonsterInfo(CharacterStatus::NewStatus(6, 4, 8), 12, 12, 4, "스켈레톤", 25, 15)
	};
	vector<FMonsterInfo> stage4 = {
		FMonsterInfo(CharacterStatus::NewStatus(8, 5, 10), 15, 15, 3, "오크", 30, 20)
	};
	vector<FMonsterInfo> stage5 = {
		FMonsterInfo(CharacterStatus::NewStatus(12, 8, 15), 20, 20, 5, "드래곤", 50, 30)
	};
	vector<vector<FMonsterInfo>> dungeonStages = { stage1, stage2, stage3, stage4, stage5 };


	//Generate new Dungeon
	if (dungeonptr)
	{
		delete dungeonptr;
		dungeonptr = nullptr;
	}
	dungeonptr = new Dungeon(dungeonStages);

}


void GameManager::InitializeGame() 
{
	//TODO : adapting Dialog/Options class
	Sleep(1000);
	cout << "\n===========================================\n";
	cout << "\n안녕하신가 용사여.\n\n";
	cout << "놀라지 말게. 자네의 3D세상은 멀쩡하다네.\n\n";
	cout << "다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가? \n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "\n===========================================\n";
	cout << "\n그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세.\n\n";
	cout << "자, 이제 게임을 시작하지\n\n";
	cout << "준비가 되었는가?\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "\n===========================================\n";
	cout << "\n[System] 이해할 수 없는 곳이다. \n\n "
		<< "1. 게임을 시작한다. \n\n 2. 당장 도망친다. \n\n당신의 선택은 ? 선택지를 입력해주세요\n";
	cout << "\n===========================================\n";
	char titleChoice;
	cin >> titleChoice;
	cin.ignore();
	system("cls");
	Sleep(1000);
	if (titleChoice == '1')
	{
		cout << "\n===========================================\n";
		cout << "\n[System] 도망치려 했지만, 이미 늦었다.\n\n게임을 시작할 수 밖에.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
	}
	else
	{
		cout << "\n===========================================\n";
		cout << "\n[System] 잘못된 선택입니다. 게임을 시작합니다.\n";
		cout << "\n===========================================\n";
		Sleep(2000);
	}
	system("cls");
	cout << "\n===========================================\n";
	cout << "\n[System] 당신의 이름을 입력하시오. \n"
		<< "\n이름은 20자 이내로 입력해주세요.  \n ";
	cout << "\n===========================================\n" << endl;
	string inputName;
	getline(cin, inputName);
	system("cls");
	if (inputName.length() > 20)
	{
		inputName = inputName.substr(0, 20);
	}
	playerPtr->SetName(inputName);
	Sleep(2000);
	SetGameState(EGameState::TITLE);
}


void GameManager::RunProcessTitle() 
{
	mapList[EGameState::TITLE]->Enter(playerPtr);

	char menuChoice;
	cin >> menuChoice;
	cin.ignore(1024, '\n');
	Sleep(1000);
	switch (menuChoice)
	{
		case '1': SetGameState(EGameState::VILLAGE); break;
		case '2': SetGameState(EGameState::DUNGEON); break;
		case '3': SetGameState(EGameState::GAME_OVER); break;
		default: cout << "[System] 잘못된 입력입니다.\n"; break;
	}
	system("cls");
}

void GameManager::RunProcessVillage()
{
	
	Village* village = static_cast<Village*>(mapList[EGameState::VILLAGE]);

	Healer* healer = new Healer("앤더슨", 15);
    Merchant* merchant = new Merchant("토니");
	
	village->AddNPC(healer);
	village->AddNPC(merchant);
	
	//TODO : 아이템 리스트 정보를 csv에서 불러와 배열 push해주는 메서드 추가
	//TODO : 반복되는기능 함수로 묶기
	merchant->AddItemForSale("초보자의 검", 50);
	merchant->AddItemForSale("철검", 80);
	merchant->AddItemForSale("초보자의 갑옷", 60);
	merchant->AddItemForSale("가죽갑옷", 100);

	//Choice in Village
	mapList[EGameState::VILLAGE]->Enter(playerPtr);

	char villageChoice;
	cin >> villageChoice;
	cin.ignore(1024, '\n');

	Sleep(2000);
	system("cls");
	switch (villageChoice)
	{
		case '1':
		{
			village->InteractWithNPC(playerPtr, healer);
			SetGameState(EGameState::VILLAGE);
			delete healer;
			healer = nullptr;
			break;
		}
		case '2':
		{
			village->InteractWithNPC(playerPtr, merchant);
			SetGameState(EGameState::VILLAGE);
			delete merchant;
			merchant = nullptr;
			break;
		}
		case '3':
		{
			SetGameState(EGameState::TITLE); break;
		}
		default: 
			cout << "[System] 잘못된 입력입니다.\n"; break;
	}
	system("cls");
}

void GameManager::RunProcessDungeon()
{
	//generate monsters in the dungeon
	if (!dungeonptr)
		InitializeDungeon();

	dungeonptr->Enter(playerPtr);

	DungeonStage* stage = dungeonptr->GetCurrentStage();

	if (stage) 
	{
		stage->EnterStage();
	}
	else
	{
		cout << "[System] 유효한 던전 스테이지가 존재하지 않습니다.\n[System] 마을로 돌아갑니다." << endl;
		SetGameState(EGameState::VILLAGE);
		return;
	}

	vector<Monster*> monsters = stage->GetMonsters();


	char dungeonChoice;
	cin >> dungeonChoice;
	cin.ignore(1024, '\n');
	Sleep(2000);
	system("cls");
	switch (dungeonChoice)
	{
		case '1':
		{
			//Check if there are any monsters left in the dungeon
			if (monsters.empty())
			{
				cout << "\n===========================================\n";
				cout << "[System] 던전에는 더 이상 몬스터가 없습니다.\n";
				cout << "===========================================\n" << endl;
				Sleep(2000);
				system("cls");
				SetGameState(EGameState::VILLAGE);
				return;
			}

			//Generate a random index 
			srand(static_cast<unsigned int>(time(NULL))); // 현재 시간을 시드로 사용
			size_t randomIndex = rand() % monsters.size();
			Monster* randomMonster = monsters[randomIndex];

			//Start Battle with the random monster
			bool isPlayerAlive = dungeonptr->EncounterMonster(playerPtr, randomMonster);
			Sleep(2000);
			system("cls");
			if (isPlayerAlive == false)
			{
				GameOverProcess();
				return;
			}
			SetGameState(EGameState::DUNGEON);
			break;
		}
		case '2':
		{
			cout << "\n===========================================\n";
			cout << "[System] 무모한 도전이 반드시 정답은 아닙니다.\n";
			cout << "[System] 마을로 복귀합니다.\n";
			cout << "===========================================\n" << endl;
			Sleep(2000);
			system("cls");
			SetGameState(EGameState::VILLAGE);
			break;
		}
	}
	/*delete goblin;
	delete slime;
	delete orc;
	delete skeleton;
	delete dragon;*/
}

void GameManager::GameOverProcess()
{
	//TODO : 던전에서 죽었을때 마을로 돌아가는것이 아니라 종료되는문제 해결
	cout << "\n===========================================\n";
	cout << "\n[System] 게임이 종료되었습니다.\n";
	cout << "\n[System] 다시 시작하려면 게임을 재실행해주세요.\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	SetGameState(EGameState::GAME_OVER);
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
		delete map.second; 
	}
	mapList.clear();
}