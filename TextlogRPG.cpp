#include <iostream>
#include <windows.h>
#include <cstdint>
#include <string>
#include "TextlogRPG/GameMode/GameMode.h"

using namespace std;

int main()
{

	//Game Start Settings
	//GameMode gameMode;
	//gameMode.SetGameState(EGameState::TITLE);
	string playerName; //playername
	int32_t healCost = 5; //healing cost

	//게임 루프
	while (true)
	{
		//Dialogue 1
		Sleep(1000);
		cout << "===========================================" << endl;
		cout << "\n안녕하신가 용사여.\n\n" << endl;
		cout << "놀라지 말게. 자네의 3D세상은 멀쩡하다네.\n\n" << endl;
		cout << "다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가? \n" << endl;
		cout << "===========================================" << endl;
		Sleep(2000);
		system("cls");
		Sleep(1000);
		cout << "===========================================" << endl;
		cout << "\n그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 새로운 세상일세.\n\n" << endl;
		cout << "자, 이제 게임을 시작하지\n\n" << endl;
		cout << "준비가 되었는가?\n" << endl;
		cout << "===========================================" << endl;
		Sleep(2000);
		system("cls");
		Sleep(1000);
		cout << "\n===========================================\n" << endl;
		cout << "[System] 이해할 수 없는 곳이다. \n "
			<< "1. 게임을 시작한다. \n 2. 당장 도망친다. \n당신의 선택은 ? 선택지를 입력해주세요\n";
		cout << "\n===========================================\n" << endl;
		char choice;
		cin >> choice;
		cin.ignore(); 
		system("cls");
		Sleep(1000);
		if (choice == '1')
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
		string input;
		getline(cin, input);
		system("cls");
		if (input.length() > 20)
		{
			input = input.substr(0, 20); 
		}
		playerName = input;
		break;
	}

	Sleep(2000);
	cout << "\n===========================================\n" << endl;
	cout << "[System] 환영합니다, 용사" << playerName << "님!\n" << endl;
	cout << "이제 당신의 모험이 시작됩니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");

	while (true)
	{
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
		cin.ignore(); 
		system("cls");
		Sleep(1000);
		//마을을 선택하는 경우
		if (menuChoice == '1')
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
			cin.ignore(); 
			system("cls");
			Sleep(1000);
			if (villageChoice == '1')
			{
				cout << "\n===========================================\n" << endl;
				cout << "[System] 힐러를 만났습니다.\n" << endl;
				cout << "===========================================\n" << endl;
				//TODO : 힐러 만나기 로직 구현
				Sleep(2000);
				system("cls");
				cout << "\n===========================================\n" << endl;
				cout << "당신이 바로 말로만 듣던 바로 그.. " << playerName << " 용사님이군요!\n" << endl;
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
					cout << "\n===========================================\n" << endl;
					cout << "[System] 치유가 완료되었습니다. 체력이 회복되었습니다.\n" << endl;
					cout << "===========================================\n" << endl;
					Sleep(2000);
					system("cls");
				}
				else if (healerChoice == '2')
				{
					//TODO : 치유 거부 로직 구현
					cout << "\n===========================================\n" << endl;
					cout << "[System] 치유를 거부하셨습니다.\n" << endl;
					cout << "===========================================\n" << endl;
					Sleep(2000);
					system("cls");
				}
				else
				{
					//TODO : 잘못된 선택 처리 로직 구현
					cout << "\n===========================================\n" << endl;
					cout << "[System] 잘못된 선택입니다. 마을을 나갑니다.\n" << endl;
					cout << "===========================================\n" << endl;
					Sleep(2000);
					system("cls");
				}
				
			}
			else if (villageChoice == '2')
			{
				cout << "\n===========================================\n" << endl;
				cout << "[System] 상인을 만나 아이템을 구매합니다.\n" << endl;
				cout << "===========================================\n" << endl;
				//TODO : 상인 만나기 로직 구현
				Sleep(2000);
				system("cls");
				cout << "\n===========================================\n" << endl;
				cout << "자네인가? 요즘 호구라 불리는 그 " << playerName << "라는 용사가?\n" << endl;
				cout << "크흠흠.. 아니 됐네. 그래서 내게 뭘 원하나?\n" << endl;
				cout << "1. 무기를 구매한다.\n2. 방어구를 구매한다..\n3. 잡템을 판매한다" << endl;
				cout << "\n===========================================\n" << endl;
				char merchantChoice;
				cin >> merchantChoice;
				cin.ignore(); 
				system("cls");
				Sleep(1000);
				if (merchantChoice == '1')
				{
					cout << "\n===========================================\n" << endl;
					cout << "[System] 무기를 구매합니다.\n" << endl;
					cout << "===========================================\n" << endl;
					//TODO : 무기 구매 로직 구현
					Sleep(2000);
					system("cls");
				}
				else if (merchantChoice == '2')
				{
					cout << "\n===========================================\n" << endl;
					cout << "[System] 방어구를 구매합니다.\n" << endl;
					cout << "===========================================\n" << endl;
					//TODO : 방어구 구매 로직 구현
					Sleep(2000);
					system("cls");
				}
				else if (merchantChoice == '3')
				{
					cout << "\n===========================================\n" << endl;
					cout << "[System] 잡템을 판매합니다.\n" << endl;
					cout << "===========================================\n" << endl;
					//TODO : 잡템 판매 로직 구현
					Sleep(2000);
					system("cls");
				}
				else
				{
					cout << "\n===========================================\n" << endl;
					cout << "[System] 잘못된 선택입니다. 마을을 나갑니다.\n" << endl;
					cout << "===========================================\n" << endl;
					//TODO : 잘못된 선택 처리 로직 구현
					Sleep(2000);
				}
			}
			else if (villageChoice == '3')
			{
				cout << "\n===========================================\n" << endl;
				cout << "[System] 마을에서 나갑니다.\n" << endl;
				cout << "===========================================\n" << endl;
				Sleep(2000);
			}
			else
			{
				cout << "\n===========================================\n" << endl;
				cout << "[System] 잘못된 선택입니다. 마을에서 나갑니다.\n" << endl;
				cout << "===========================================\n" << endl;
				Sleep(2000);
			}
		}
		//던전을 선택하는 경우
		else if (menuChoice == '2')
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
			cout << "[System] " << endl;
			
		}
		//게임종료를 선택하는 경우
	}

	




}
