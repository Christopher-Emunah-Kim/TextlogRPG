#include "Dungeon.h"

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

void Dungeon::EncounterMonster(Player* player, Monster* monster) {
	if (monster) 
	{
		// TODO : 전투 시스템 호출
		// 예: monster->Attack(player);
	}
}
