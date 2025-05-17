#pragma once
#include <map>

using namespace std;

enum class Direction
{
	North,
	South,
	East,
	West
};

class Room
{
private:
	//방 위치정보
	int positionX, positionY;

	//연결된 방 정보 map
	map<Direction, Room*> connectedRooms;

public:
	//생성자
	Room(int x, int y) : positionX(x), positionY(y) {}

	//처음 다른 방과 연결하는 함수
	void connectRoom(Direction dir, Room* room);

	//연결된 방이 있는지 확인하는 함수
	Room* getConnectedRoom(Direction dir);

	//방 위치정보 얻는 함수
	inline int getPositionX() const { return positionX; }
	inline int getPositionY() const { return positionY; }

};

