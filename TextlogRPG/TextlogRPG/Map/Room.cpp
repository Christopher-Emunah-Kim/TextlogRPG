#include "../Map/Room.h"

//처음 다른 방과 연결하는 함수
void Room::connectRoom(Direction dir, Room* other)
{
	connectedRooms[dir] = other;
}

Room* Room::getConnectedRoom(Direction dir)
{
	if (connectedRooms.find(dir) != connectedRooms.end())
	{
		return connectedRooms[dir];
	}
	else
	{
		return nullptr; //해당 방향엔 연결된 방이 없음.
	}
}
