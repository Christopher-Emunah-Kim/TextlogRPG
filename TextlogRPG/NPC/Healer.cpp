#include "Healer.h"

void Healer::HealPlayer(Player* player, int32_t cost)
{
	if (player->GetPlayerData().playerGold >= cost) 
	{
		int32_t healAmount = player->GetCharacterInfo().maxHealth - player->GetCharacterInfo().health;
		player->Heal(healAmount);
		player->UseGold(cost);
		cout << "\n===========================================\n" << endl;
		cout << "[System] 힐러 " << npcInfo.npcName << "가 치유를 시작합니다." << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		cout << "\n===========================================\n" << endl;
		cout << "[System] 치유가 완료되었습니다. \n" << healAmount << "의 체력이 회복되었습니다.\n" << endl;
		cout << "[System] 치유의 집을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	else 
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 골드가 부족하네요... \n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
}

void Healer::Interact(Player* player)
{
	cout << "\n===========================================\n" << endl;
	cout << "[System] 치유의 집에서 힐러 " << npcInfo.npcName << "를 만났습니다.\n" << endl;
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
		HealPlayer(player, healCost);
		Sleep(2000);
		system("cls");
		
	}
	else if (healerChoice == '2')
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 치유를 거부하셨습니다.\n치유의 집을 떠나 길거리로 나갑니다." << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	else
	{
		//TODO : 잘못된 선택 처리 로직 구현
		cout << "\n===========================================\n" << endl;
		cout << "[System] 잘못된 선택입니다. 치유의 집을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	
}

