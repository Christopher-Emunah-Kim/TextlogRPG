#include <iostream>
#include <windows.h>
#include "TextlogRPG/GameMode/GameMode.h"

int main()
{
	using namespace std;

	//Game Start Settings
	GameMode gameMode;
	gameMode.SetGameState(EGameState::TITLE);



	//Dialogue 1
	Sleep(1500);
	cout << "===========================================" << endl; Sleep(800);
	cout << "\n안녕하신가 용사여.\n\n" << endl; Sleep(800);
	cout << "놀라지 말게. 자네의 3D세상은 멀쩡하다네.\n\n" << endl; Sleep(800);
	cout << "다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가? \n" << endl; Sleep(800);
	cout << "===========================================" << endl; Sleep(6000);
	system("cls");

	Sleep(1000);
	cout << "===========================================" << endl; Sleep(800);
	cout << "\n그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세.\n\n" << endl; Sleep(800);
	cout << "자, 이제 게임을 시작하지\n\n" << endl; Sleep(800);
	cout << "준비가 되었는가?\n" << endl; Sleep(800);
	cout << "===========================================" << endl; Sleep(6000);




}
