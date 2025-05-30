#include "GameManager.h"

#include "../Character/Player.h"
#include "../Character/Monster.h"
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




GameManager::GameManager(const GameMode& gm, Player* player)
	: gameMode(GameMode(gm.GetGameState())), playerPtr(player)
{
	maps.insert(make_pair(EGameState::TITLE, new Title()));
	maps.insert(make_pair(EGameState::VILLAGE, new Village()));
	maps.insert(make_pair(EGameState::DUNGEON, new Dungeon()));
}



void GameManager::Run() 
{
    InitializeGame();

	//TODO : 레벨 데이터 초기값 끌어오기
    while (gameMode.GetGameState() != EGameState::GAME_OVER) 
	{
        switch (gameMode.GetGameState()) 
		{
            case EGameState::TITLE: RunProcessTitle(); break;
            case EGameState::VILLAGE: RunProcessVillage(); break;
            case EGameState::DUNGEON: RunProcessDungeon(); break;
            default: gameMode.SetGameState(EGameState::GAME_OVER); break;
        }
    }
}

void GameManager::InitializeGame() 
{
	//TODO : Dialog/Options 유틸 클래스 적용
	//First Dialogue
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
		cout << "\n[System] 도망치려 했지만, 이미 늦었다.\n게임을 시작할 수 밖에.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
	}
	else
	{
		cout << "\n===========================================\n";
		cout << "[System] 잘못된 선택입니다. 게임을 시작합니다.";
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
	gameMode.SetGameState(EGameState::TITLE);
}


void GameManager::RunProcessTitle() 
{
	maps[EGameState::TITLE]->Enter(playerPtr);

	char menuChoice;
	cin >> menuChoice;
	cin.ignore(1024, '\n');
	Sleep(1000);
	switch (menuChoice)
	{
		case '1': gameMode.SetGameState(EGameState::VILLAGE); break;
		case '2': gameMode.SetGameState(EGameState::DUNGEON); break;
		case '3': gameMode.SetGameState(EGameState::GAME_OVER); break;
		default: cout << "[System] 잘못된 입력입니다.\n"; break;
	}
	system("cls");
}

void GameManager::RunProcessVillage()
{
	
	Village* village = static_cast<Village*>(maps[EGameState::VILLAGE]);

	Healer* healer = new Healer("앤더슨", 15);
    Merchant* merchant = new Merchant("토니");
	
	village->AddNPC(healer);
	village->AddNPC(merchant);
	
	//TODO : 아이템 리스트 정보를 csv에서 불러와 배열 push해주는 메서드 추가
	//TODO : 반복되는기능 함수로 묶기
	ItemManager& itemManager = ItemManager::GetInstance();

	Weapon* basicSword = new Weapon();
	basicSword->SetItem(EItemType::WEAPON, 50, 10, 0, 0, "초보자의 검");
	itemManager.RegisterItem(basicSword);
	merchant->AddItemForSale(basicSword, 50);

	Weapon* ironSword = new Weapon();
	ironSword->SetItem(EItemType::WEAPON, 80, 15, 0, 0, "철검");
	itemManager.RegisterItem(ironSword);
	merchant->AddItemForSale(ironSword, 80);

	Armor* basicArmor = new Armor();
	basicArmor->SetItem(EItemType::ARMOR, 60, 0, 10, 0, "초보자의 갑옷");
	itemManager.RegisterItem(basicArmor);
	merchant->AddItemForSale(basicArmor, 60);

	Armor* leatherArmor = new Armor();
	leatherArmor->SetItem(EItemType::ARMOR, 100, 0, 15, 2, "가죽갑옷");
	itemManager.RegisterItem(leatherArmor);
	merchant->AddItemForSale(leatherArmor, 100);


	//Choice in Village
	maps[EGameState::VILLAGE]->Enter(playerPtr);


	//TODO : 힐러를 만나 체력을 회복하기
	//TODO : 상인을 만나 아이템을 구매하기
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
			gameMode.SetGameState(EGameState::VILLAGE);
			delete healer;
			healer = nullptr;
			break;
		}
		case '2':
		{
			village->InteractWithNPC(playerPtr, merchant);
			gameMode.SetGameState(EGameState::VILLAGE);
			delete merchant;
			merchant = nullptr;
			break;
		}
		case '3':
		{
			gameMode.SetGameState(EGameState::TITLE); break;
		}
		default: 
			cout << "[System] 잘못된 입력입니다.\n"; break;
	}
	system("cls");
}

void GameManager::RunProcessDungeon()
{
	maps[EGameState::DUNGEON]->Enter(playerPtr);

	//필요한 몹을 생성
	//TODO : 몬스터 생성 로직 구현
    Dungeon* dungeon = static_cast<Dungeon*>(maps[EGameState::DUNGEON]);	
	//Monster(const string& name, int32_t health, int32_t attack, int32_t defense, int32_t agility, short level, int32_t exp, int32_t gold);
	Monster* goblin = new Monster("고블린", 10, 5, 3, 5, 1, 20, 10);
	Monster* slime = new Monster("슬라임", 8, 4, 2, 1, 2, 15, 5);
	Monster* orc = new Monster("오크", 15, 8, 5, 10, 3, 30, 20);
	Monster* skeleton = new Monster("스켈레톤", 12, 6, 4, 8, 4, 25, 15);
	Monster* dragon = new Monster("드래곤", 25, 12, 8, 15, 5, 50, 30);

	//던전에 추가
	dungeon->AddMonster(goblin);
	dungeon->AddMonster(slime);
	dungeon->AddMonster(orc);
	dungeon->AddMonster(skeleton);
	dungeon->AddMonster(dragon);

	vector<Monster*>& monsters = dungeon->GetMonsterList();

	char dungeonChoice;
	cin >> dungeonChoice;
	cin.ignore(1024, '\n');
	Sleep(2000);
	system("cls");
	switch (dungeonChoice)
	{
		case '1':
		{
			//dungeon의 몬스터 리스트 중 랜덤 하나를 골라
			if (monsters.empty())
			{
				cout << "\n===========================================\n";
				cout << "[System] 던전에는 더 이상 몬스터가 없습니다.\n";
				cout << "===========================================\n" << endl;
				Sleep(2000);
				system("cls");
				gameMode.SetGameState(EGameState::VILLAGE);
				return;
			}
			int randomIndex = rand() % monsters.size();
			Monster* randomMonster = monsters[randomIndex];
			dungeon->EncounterMonster(playerPtr, randomMonster);
			Sleep(2000);
			system("cls");
			gameMode.SetGameState(EGameState::DUNGEON);
		}
		case '2':
		{
			cout << "\n===========================================\n";
			cout << "[System] 무모한 도전이 반드시 정답은 아닙니다.\n";
			cout << "[System] 마을로 복귀합니다.\n";
			cout << "===========================================\n" << endl;
			Sleep(2000);
			system("cls");
			gameMode.SetGameState(EGameState::VILLAGE);
			break;
		}
	}
	delete goblin;
	delete slime;
	delete orc;
	delete skeleton;
	delete dragon;
}
//
//void GameManager::RunProcessCombat()
//{
//	string monsterName;
//
//	cout << "\n===========================================\n" << endl;
//	cout << "[System] 당신은 심연에 잠겨듭니다..\n" << endl;
//	cout << "===========================================\n" << endl;
//	Sleep(2000);
//	system("cls");
//	//TODO : 몬스터 정보 출력 로직
//	cout << "\n===========================================\n" << endl;
//	cout << "[System] 몬스터" << monsterName<< "이 당신의 앞에 등장했습니다.\n" << endl;
//	//몬스터 정보 출력
//	cout << "===========================================\n" << endl;
//	Sleep(2000);
//	system("cls");
//	cout << "\n===========================================\n" << endl;
//	cout << "[System] 전투를 시작합니다.\n" << endl;
//	cout << "===========================================\n" << endl;
//	Sleep(2000);
//	system("cls");
//	//TODO : 전투 로직 구현
//	bool isVictory = true;
//	if (!isVictory)
//	{
//		cout << "\n===========================================\n" << endl;
//		cout << "[System] 처절한 싸움 끝에, 당신은 승리하였습니다.\n" << endl;
//		cout << "===========================================\n" << endl;
//		Sleep(2000);
//		system("cls");
//		//TODO : 전리품, 골드, 경험치 획득 로직 구현
//		//player->GainLoot();
//		gameMode.SetGameState(EGameState::DUNGEON);
//	}
//	else
//	{
//		cout << "\n===========================================\n" << endl;
//		cout << "[System] 패배. 여신의 품으로 돌아갑니다...\n" << endl;
//		cout << "===========================================\n" << endl;
//		Sleep(2000);
//		system("cls");
//		gameMode.SetGameState(EGameState::VILLAGE);
//		//패배시 마을로 돌아가는 로직 구현
//	}
//}


GameManager::~GameManager()
{
	if (playerPtr) 
	{
		delete playerPtr;
		playerPtr = nullptr; 
	}

	for (const pair<EGameState, Area*>& map : maps)
	{
		delete map.second; // Delete each Area object
		maps[map.first] = nullptr; // Set pointer to nullptr after deletion
	}
	maps.clear();
	cout << "\n===========================================\n";
	cout << "[System] 게임이 종료되었습니다.";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
}