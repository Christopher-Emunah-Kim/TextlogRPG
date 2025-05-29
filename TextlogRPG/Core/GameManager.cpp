#include "GameManager.h"

#include "../Dialog/Dialog.h"
#include "../Dialog/Option.h"

#include "../Character/Player.h"
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
	cout << "===========================================" << endl;
	cout << "\n안녕하신가 용사여.\n\n" << endl;
	cout << "놀라지 말게. 자네의 3D세상은 멀쩡하다네.\n\n" << endl;
	cout << "다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가? \n" << endl;
	cout << "===========================================" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "===========================================" << endl;
	cout << "\n그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세.\n\n" << endl;
	cout << "자, 이제 게임을 시작하지\n\n" << endl;
	cout << "준비가 되었는가?\n" << endl;
	cout << "===========================================" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "\n===========================================\n" << endl;
	cout << "[System] 이해할 수 없는 곳이다. \n\n "
		<< "1. 게임을 시작한다. \n\n 2. 당장 도망친다. \n\n당신의 선택은 ? 선택지를 입력해주세요\n";
	cout << "\n===========================================\n" << endl;
	char titleChoice;
	cin >> titleChoice;
	cin.ignore();
	system("cls");
	Sleep(1000);
	if (titleChoice == '1')
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 도망치려 했지만, 이미 늦었다.\n게임을 시작할 수 밖에." << endl;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
	}
	else
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 잘못된 선택입니다. 게임을 시작합니다." << endl;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
	}
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "[System] 당신의 이름을 입력하시오. \n"
		<< "이름은 20자 이내로 입력해주세요.  \n ";
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
	currentAreaPtr = new Title();
	currentAreaPtr->Enter(playerPtr);

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
	Village* village = new Village();
	currentAreaPtr = village;

	Healer* healer = new Healer("앤더슨", 10);
    Merchant* merchant = new Merchant("토니");
	
	village->AddNPC(healer);
	village->AddNPC(merchant);
	
	//TODO : 아이템 추가 및 상인에게 아이템 push
	//TODO : 아이템 리스트 정보를 불러와 배열 push해주는 메서드 추가
	ItemManager& itemManager = ItemManager::GetInstance();
	Weapon* sword = new Weapon();
	sword->SetItem(EItemType::WEAPON, 80, 15, 0, 0, "철검");
	Armor* armor = new Armor();
	armor->SetItem(EItemType::ARMOR, 100, 0, 15, 2, "가죽갑옷");

	itemManager.RegisterItem(sword);
	itemManager.RegisterItem(armor);

	merchant->AddItemForSale(sword, 80);
	merchant->AddItemForSale(armor, 100);

	//Choice in Village
	currentAreaPtr->Enter(playerPtr);

	Sleep(2000);
	system("cls");

	//TODO : 힐러를 만나 체력을 회복하기
	//TODO : 상인을 만나 아이템을 구매하기
	char villageChoice;
	cin >> villageChoice;
	cin.ignore(1024, '\n');
	Sleep(1000);
	switch (villageChoice)
	{
		case '1':
		{
			village->InteractWithNPC(playerPtr, healer);
			RunProcessHealer(healer);
			break;
		}
		case '2':
		{
			village->InteractWithNPC(playerPtr, merchant);
			RunProcessMerchant(merchant);
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

void GameManager::RunProcessHealer(Healer* healer)
{
	//TODO : 힐링 가격 데이터레이블 만들기
	int32_t healCost = healer->GetHealCost();
	int32_t healAmount = playerPtr->GetCharacterInfo().maxHealth - playerPtr->GetCharacterInfo().health;

	healer->Interact(playerPtr);

	delete healer;

	gameMode.SetGameState(EGameState::VILLAGE);
}

void GameManager::RunProcessMerchant(Merchant* merchant)
{
	merchant->Interact(playerPtr);

	delete merchant;

	gameMode.SetGameState(EGameState::VILLAGE);
}

void GameManager::RunProcessDungeon()
{
	currentAreaPtr = new Dungeon();
	currentAreaPtr->Enter(playerPtr);

	char dungeonChoice;
	cin >> dungeonChoice;
	cin.ignore(1024, '\n');
	Sleep(2000);
	system("cls");
	switch (dungeonChoice)
	{
	case '1':
	{
		//TODO : 전투 로직
		Sleep(2000);
		system("cls");
		gameMode.SetGameState(EGameState::BATTLE);
	}
	case '2':
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 무모한 도전이 반드시 정답은 아닙니다.\n" << endl;
		cout << "[System] 마을로 복귀합니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		gameMode.SetGameState(EGameState::VILLAGE);
		break;
	}
	}
}

void GameManager::RunProcessCombat()
{
	string monsterName;

	cout << "\n===========================================\n" << endl;
	cout << "[System] 당신은 심연에 잠겨듭니다..\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	//TODO : 몬스터 정보 출력 로직
	cout << "\n===========================================\n" << endl;
	cout << "[System] 몬스터" << monsterName<< "이 당신의 앞에 등장했습니다.\n" << endl;
	//몬스터 정보 출력
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "[System] 전투를 시작합니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	//TODO : 전투 로직 구현
	bool isVictory = true;
	if (!isVictory)
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 처절한 싸움 끝에, 당신은 승리하였습니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		//TODO : 전리품, 골드, 경험치 획득 로직 구현
		//player->GainLoot();
		gameMode.SetGameState(EGameState::DUNGEON);
	}
	else
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 패배. 여신의 품으로 돌아갑니다...\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		gameMode.SetGameState(EGameState::VILLAGE);
		//패배시 마을로 돌아가는 로직 구현
	}
}


GameManager::~GameManager()
{

	if (playerPtr) delete playerPtr;
	if (currentAreaPtr) delete currentAreaPtr;

}