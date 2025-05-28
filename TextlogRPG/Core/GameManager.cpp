#include "GameManager.h"
#include "../Dialog/Dialog.h"
#include "../Dialog/Option.h"
#include "../Character/Player.h"

void GameManager::Run() {
    InitializeGame();
	// 플레이어 생성, 초기 상태 설정 등
	//TODO : 레벨 데이터 초기값 끌어오기
    while (gameMode.GetGameState() != EGameState::GAME_OVER) 
	{
        switch (gameMode.GetGameState()) 
		{
            case EGameState::TITLE: RunProcessTitle(); break;
            case EGameState::VILLAGE: RunProcessVillage(); break;
            case EGameState::HEALER: RunProcessHealer(); break;
            case EGameState::MERCHANT: RunProcessMerchant(); break;
            case EGameState::DUNGEON: RunProcessDungeon(); break;
            default: gameMode.SetGameState(EGameState::GAME_OVER); break;
        }
    }
}

void GameManager::InitializeGame() 
{
	//TITLE Dialogue
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
	player->SetName(inputName);
	gameMode.SetGameState(EGameState::TITLE);
}


void GameManager::RunProcessTitle() 
{
	Sleep(2000);
	cout << "\n===========================================\n" << endl;
	cout << "[System] 환영합니다, 용사" << player->GetName() << "님!\n" << endl;
	cout << "이제 당신의 모험이 시작됩니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "\n===========================================\n" << endl;
	cout << "[System] 타이틀을 출력중입니다....\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	cout << "\n===========================================\n" << endl;
	cout << "[System] 타이틀 화면입니다.\n" << endl;
	cout << "1. 마을로 가기\n2. 던전에 가기\n3. 게임을 떠나기\n" << endl;
	cout << "===========================================\n" << endl;
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
	cout << "\n===========================================\n" << endl;
	cout << "[System] 마을로 이동합니다..." << endl;
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	//힐러를 만나 체력을 회복하기
	//상인을 만나 아이템을 구매하기
	cout << "\n===========================================\n" << endl;
	cout << "[System] 마을에 도착했습니다.\n" << endl;
	cout << "1. 힐러 만나기\n2. 상인 만나기\n3. 마을 나가기\n" << endl;
	cout << "===========================================\n" << endl;
	char villageChoice;
	cin >> villageChoice;
	cin.ignore(1024, '\n');
	Sleep(1000);
	switch (villageChoice)
	{
		case '1': gameMode.SetGameState(EGameState::HEALER); break;
		case '2': gameMode.SetGameState(EGameState::MERCHANT); break;
		case '3': gameMode.SetGameState(EGameState::TITLE); break;
		default: cout << "[System] 잘못된 입력입니다.\n"; break;
	}
	system("cls");
}

void GameManager::RunProcessHealer()
{
	//TODO : 힐링 가격 데이터레이블 만들기
	int16_t healCost = 10;
	int32_t healAmount = player->GetCharacterInfo().maxHealth - player->GetCharacterInfo().health;
	
	cout << "\n===========================================\n" << endl;
	cout << "[System] 치유의 집에서 힐러를 만났습니다.\n" << endl;
	cout << "===========================================\n" << endl;
	//TODO : 힐러 만나기 로직 구현
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "당신이 바로 말로만 듣던 바로 그.. " << player->GetName() << " 용사님이군요!\n" << endl;
	cout << "안색이 좋지 않네요. 치유가 필요하신가요?\n" << endl;
	cout << "1. 네, 치유해주세요.(" << healCost << "골드)\n2.아니요, 괜찮습니다.\n" << endl;
	cout << "===========================================\n" << endl;
	char healerChoice;
	cin >> healerChoice;
	cin.ignore();
	Sleep(2000);
	system("cls");
	if (healerChoice == '1')
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 치유를 시작합니다...\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		//TODO : 치유 로직 구현
		if (player->GetPlayerData().playerGold >= healCost)
		{
			player->Heal(healAmount);
			player->UseGold(healCost);
			cout << "\n===========================================\n" << endl;
			cout << "[System] 치유가 완료되었습니다. \n" << healAmount << "의 체력이 회복되었습니다.\n" << endl;
			cout << "===========================================\n" << endl;
		}
		else
		{
			cout << "\n===========================================\n" << endl;
			cout << "[System] 골드가 부족합니다...\n" << endl;
			cout << "===========================================\n" << endl;
		}
		
		Sleep(2000);
		system("cls");
		gameMode.SetGameState(EGameState::VILLAGE);
	}
	else if (healerChoice == '2')
	{
		//TODO : 치유 거부 로직 구현
		cout << "\n===========================================\n" << endl;
		cout << "[System] 치유를 거부하셨습니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		gameMode.SetGameState(EGameState::VILLAGE);
	}
	else
	{
		//TODO : 잘못된 선택 처리 로직 구현
		cout << "\n===========================================\n" << endl;
		cout << "[System] 잘못된 선택입니다. 치유의 집을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		gameMode.SetGameState(EGameState::VILLAGE);
		system("cls");
	}
}

void GameManager::RunProcessMerchant()
{
	cout << "\n===========================================\n" << endl;
	cout << "[System] 상인을 만나 아이템을 구매합니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "자네인가? 요즘 호구라 불리는 그 " << player->GetName() << "라는 용사가?\n" << endl;
	cout << "크흠흠.. 아니 됐네. 그래서 내게 뭘 원하나?\n" << endl;
	cout << "1. 무기를 구매한다.\n2. 방어구를 구매한다..\n3. 잡템을 판매한다.\n4. 마을로 돌아간다." << endl;
	cout << "\n===========================================\n" << endl;
	char merchantChoice;
	cin >> merchantChoice;
	cin.ignore(1024, '\n');
	system("cls");
	Sleep(1000);
	//TODO : 아이템 구매/판매 로직 구현
	//TODO : 아이템 레이블 정보 불러오기 구현
	int32_t itemPrice = 100;
	string itemName = "UNKNOWN";

	switch (merchantChoice) {
	case '1':
		//무기 구매
		cout << "\n===========================================\n" << endl;
		cout << "[System] "<< itemName <<"을 " << itemPrice<<" 골드에 구매했습니다.\n";
		cout << "===========================================\n" << endl;

		player->UseGold(itemPrice);
		//player->EquipItem(new Weapon);
		Sleep(2000);
		system("cls");
		break;
	case '2':
		//방어구 구매
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << itemName << "을 " << itemPrice << " 골드에 구매했습니다.\n";
		cout << "===========================================\n" << endl;
		player->UseGold(itemPrice);
		// player->EquipItem(new Armor);
		Sleep(2000);
		system("cls");
		break;
	case '3':
		//잡템 판매
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << itemName << "을 " << itemPrice << " 골드에 판매했습니다.\n";
		cout << "===========================================\n" << endl;
		player->EarnGold(5);
		//player -> LoseItem(new MiscItem);
		Sleep(2000);
		system("cls");
		break;
	case '4':
		//마을로 돌아가기
		cout << "\n===========================================\n" << endl;
		cout << "[System] 상점을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		break;
	default:
		cout << "\n===========================================\n" << endl;
		cout << "[System] 잘못된 선택입니다. 상점을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		break;
	}
	gameMode.SetGameState(EGameState::VILLAGE);
}

void GameManager::RunProcessDungeon()
{
	cout << "\n===========================================\n" << endl;
	cout << "[System] 던전 탐험을 시작합니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "[system] 기억하십시오. 심연을 들여다볼수록,\n 당신 또한 심연에 물들 것입니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	//TODO : 던전 탐험 로직 구현
	//탐색진행 or 마을로 돌아가기
	cout << "\n===========================================\n" << endl;
	cout << "[System] 던전의 입구에 도착했습니다.\n도전하시겠습니까?\n" << endl;
	cout << "1. 인생은 모험이지!\n2. 아니 지금은 아닌것 같아.(마을로 돌아간다)\n" << endl;
	cout << "===========================================\n" << endl;
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
