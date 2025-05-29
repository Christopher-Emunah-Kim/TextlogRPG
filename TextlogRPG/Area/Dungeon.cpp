#include "Dungeon.h"
#include "../Character/Player.h"
#include "../Character/Monster.h"

void Dungeon::Enter(Player* player)
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
}

void Dungeon::AddMonster(Monster* monster) {
	monsters.push_back(monster);
}

void Dungeon::RemoveMonster(Monster* monster) {
	monsters.erase(remove(monsters.begin(), monsters.end(), monster), monsters.end());
}

vector<Monster*>& Dungeon::GetMonsterList() 
{
	return monsters;
}

void Dungeon::EncounterMonster(Player* player, Monster* monster)
{
	cout << "\n===========================================\n" << endl;
	cout << "[System] " << monster->GetCharacterInfo().characterName << "과(와) 조우했습니다!\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	//TODO : 전투 로직 _ 둘의 Agility를 비교하여 먼저 공격하는 캐릭터 결정
	BaseCharacter* player1;
	BaseCharacter* player2;
	if (player->GetCharacterInfo().characterStats.GetAgility() >= monster->GetCharacterInfo().characterStats.GetAgility()) 
	{
		player1 = player;
		player2 = monster;
	}
	else {
		player1 = monster;
		player2 = player;
	}
	player1->Attack(player2);
	
	//둘 중에 하나가 쓰러질때까지 반복 //TODO 스읍 이거 전투로직 이상한데 나중에 다시보자.
	while (player1->GetCharacterInfo().health > 0 && player2->GetCharacterInfo().health > 0) 
	{
		player2->Attack(player1);

		if (player1->GetCharacterInfo().health > 0 && player2->GetCharacterInfo().health > 0) 
		{
			player1->Attack(player2);
		}
	}
	//던전 시작으로 돌아가는 로직
	cout << "\n===========================================\n" << endl;
	if (player->GetCharacterInfo().health <= 0)
	{
		cout << "[System] " << player->GetCharacterInfo().characterName << "이(가) 쓰러졌습니다.\n" << endl;
		cout << "[System] 게임 오버입니다. 마을로 돌아갑니다.\n" << endl;
	}
	else
	{
		cout << "[System] " << monster->GetCharacterInfo().characterName << "이(가) 쓰러졌습니다.\n" << endl;
		cout << "[System] 승리하였습니다! 전리품을 획득합니다.\n" << endl;
	}
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	Enter(player);

}
