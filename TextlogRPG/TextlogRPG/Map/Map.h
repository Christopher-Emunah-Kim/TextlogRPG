#pragma once
#include "Room.h"



class Map
{
private :
	//생성할 방 배열 사이즈
	static const int SIZE = 4;
	//방 배열
	Room* rooms[SIZE][SIZE];

public :
	//생성자(사이즈 기준으로 room 동적할당)
	Map();

	//특정위치의 방 얻는 함수
	Room* getRoom(int positionX, int positionY);

	//소멸자(동적할당한 room 해제)
	~Map();

};

