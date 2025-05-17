#include "Player.h"
#include "../Map/Room.h"
#include <iostream>

using namespace std;

void Player::PlayerMove(Direction dir)
{
	targetRoom = currentRoom->getConnectedRoom(dir);
	if (targetRoom != nullptr)
	{
		currentRoom = targetRoom;
		cout << "당신은" << currentRoom->getPositionX() << ", " << currentRoom->getPositionY() << " 방으로 이동했습니다." << endl;
	}
	else
	{
		cout << "당신의 앞은 단단한 벽으로 막혀있습니다. 다른 방향을 선택하세요" << endl;
	}
}
