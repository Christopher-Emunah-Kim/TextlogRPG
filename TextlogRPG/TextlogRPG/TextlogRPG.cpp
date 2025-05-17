#include <iostream>
#include <windows.h>
#include "Map/Map.h"
#include "Player/Player.h"

using namespace std;

enum class MainMenu
{
	None,
	StartGame,
	ExitGame
};

int main()
{
	//플레이할 맵 생성
	Map dungeon; 

	//플레이어 생성(시작위치 지정)
	//시작위치 난수 지정(난수 초기화)
	srand(static_cast<unsigned int>(time(0)));
	int startX = rand() % 4;
	int startY = rand() % 4;
	Player player(dungeon.getRoom(startX, startY));

	// RPG 게임의 시작을 알리는 메시지 출력
	Sleep(1500);
	cout << "===========================================" << endl; Sleep(800);
	cout << "\n안녕하신가 용사여.\n\n" << endl; Sleep(800);
	cout << "놀라지 말게. 자네의 3D세상은 멀쩡하다네.\n\n" << endl; Sleep(800);
	cout << "다만, 자네의 실력이 고작 그정도인걸 어쩌겠는가? \n" << endl; Sleep(800);
	cout << "===========================================" << endl; Sleep(6000);
	system("cls");

	Sleep(1000);
	cout << "===========================================" << endl; Sleep(800);
	cout << "\n그래, 자네 말일세.. 이곳은 자네에게 가장 잘어울리는 텍스트 던전일세.\n\n" << endl; Sleep(800);
	cout << "자, 이제 게임을 시작하지\n\n" << endl; Sleep(800);
	cout << "준비가 되었는가?\n" << endl; Sleep(800);
	cout << "===========================================" << endl; Sleep(6000);

	bool isGameStart = false; //게임 시작 여부
	while (!isGameStart)
	{
		system("cls");
		cout << "자, 어떻게 하고싶은가?\n\n"; Sleep(1200);
		//메인 메뉴 출력
		cout << "=========================================\n" << endl; 
		cout << "1. ??? 뭐가 뭔진 모르겠지만 일단 해보죠." << endl; Sleep(500);
		cout << "\n2. ??? 무슨 소리에요? 날 내보내줘요!" << endl;
		cout << "\n=========================================" << endl;
		//플레이어 게임 시작, 종료 선택
		int choice;
		cin >> choice;
		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "\n\n자네 숫자도 못읽는 멍청이였나? 마치 __int32를 모르는 어떤 멍청이가 생각나는군. 다시 말해보게" << endl; Sleep(5000);
			continue;
		}

		if (choice == 1 || choice == 2)
		{
			switch (choice)
			{
			case 1:
				system("cls");
				cout << "=========================================\n" << endl; Sleep(1000);
				cout << "\n\n좋아. 자네는 이제부터 이곳에서 살아남아야 하네." << endl; Sleep(2000);
				cout << "\n\n어디한번. 잘해보게나. 클클클...." << endl; Sleep(1000);
				cout << "\n=========================================" << endl; Sleep(4000);
				isGameStart = true; //게임 시작
				break;
			case 2:
				system("cls");
				cout << "\n\n자네는 정말로 그만두고 싶나? 자네가 이곳을 떠나면 자네는 영원히 이곳에 돌아올 수 없게 되네." << endl; Sleep(2000);
				cout << "\n\n정말로 그만두겠나? \n\n (1: 예, 2: 아니오) ";
				int exitChoice;
				cin >> exitChoice;
				if (exitChoice == 1)
				{
					cout << "\n\n자네는 정말로 그만두기로 했군. 안녕히 가게." << endl; Sleep(4000);
					system("cls");
					return 0;
				}
				else if (exitChoice == 2)
				{
					cout << "\n\n좋아. 자네는 계속 이곳에 남기로 했군. 자, 이제 어떻게 하겠나?" << endl; Sleep(4000);
					continue;
				}
				else
				{
					system("cls");
					cout << "\n\n .............. " << endl; Sleep(2000);
					cin.clear();
					cin.ignore(1024, '\n');
					cout << " \n\n오 그래 자네는 확실히 숫자를 못읽는군. 그만 꺼지시게. " << endl; Sleep(4000);
					return 0;
				}
				break;
			}
		}
		else
		{
			cout << "\n\n" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "오 맙소사, 1,2가 아니라 " << choice << "를 말한다구? 자네는 천재..........라고 말할것 같나? 다시 말해보게" << endl; Sleep(5000);
		}
	}
	
	system("cls");
	cout << "=========================================" << endl; Sleep(800);
	cout << "\n\n[System] 당신은 낯선 방에서 눈을 떴습니다." << endl; Sleep(2000);
	cout << "\n\n\n[System] 당신의 여정이 평안하길" << endl; Sleep(800);
	cout << "\n\n=========================================" << endl; Sleep(2000);

	//게임 시작 후
	while (true)
	{
		system("cls");
		//플레이어가 입력한 명령어를 받음
		cout << "\n\n자, 이제 어떻게 하면 좋을까?" << endl; Sleep(1500);
		cout << "\n=========================================" << endl;
		cout << "\n1. 동쪽으로 이동한다." << endl;
		cout << "\n2. 서쪽으로 이동한다." << endl;
		cout << "\n3. 남쪽으로 이동한다." << endl;
		cout << "\n4. 북쪽으로 이동한다." << endl;
		cout << "\n=========================================" << endl;
		
		int targetDirection;
		cin >> targetDirection; //플레이어가 입력한 방향을 받음
		//올바른 명령어가 아닐 경우 cin 버퍼 비우고 오류메시지 출력
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "\n\n[System] 놔. .놓으라고! 저 똥멍청이가 또 이상한 짓을 하잖아!" << endl; Sleep(5000);
			continue;
		}
		//플레이어가 입력한 방향에 따라 이동
		//이동가능한 방이라면 이동, 아니라면 이동 불가 메시지 출력
		system("cls");

		cout << "=========================================\n" << endl; Sleep(800);
		switch (targetDirection)
		{
		case 1:
			player.PlayerMove(Direction::East);
			break;
		case 2:
			player.PlayerMove(Direction::West);
			break;
		case 3:
			player.PlayerMove(Direction::South);
			break;
		case 4:
			player.PlayerMove(Direction::North);
			break;
		}
		cout << "\n=========================================" << endl; Sleep(4000);

	}
    return 0;
}
