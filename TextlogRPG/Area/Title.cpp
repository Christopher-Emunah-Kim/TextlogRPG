#include "Title.h"
#include "../Character/Player.h"

void Title::Enter(Player* player)
{
	cout << "\n===========================================\n" << endl;
	cout << "\n[System] 환영합니다, 용사 " << player->GetName() << " 님!\n" << endl;
	cout << "\n이제 당신의 모험이 시작됩니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "\n[System] 타이틀을 출력중입니다....\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "\n[System] 타이틀 화면입니다.\n" << endl;
	cout << "\n1. 마을로 가기\n\n2. 던전에 가기\n\n3. 게임을 떠나기\n" << endl;
	cout << "\n===========================================\n" << endl;
}

