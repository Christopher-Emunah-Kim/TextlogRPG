#include "Player.h"
#include "../Map/Room.h"
#include "Windows.h" 
#include <iostream>

using namespace std;

void Player::PlayerMove(Direction dir)
{
	//플레이어가 이동할 방.
	Room* targetRoom;

	targetRoom = currentRoom->getConnectedRoom(dir);
	if (targetRoom != nullptr)
	{
		currentRoom = targetRoom;
		Sleep(1000);
		cout << "당신은 천천히 걸음을 옮겨 새로운 방으로 이동했습니다." << endl;
		Sleep(2000);
	}
	else
	{
		Sleep(1000);
		cout << "당신의 앞은 단단한 벽으로 막혀있습니다. 다른 방향을 선택하세요" << endl;
		Sleep(1000);
	}
}
