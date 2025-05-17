#include "Map.h"
#include "../Map/Room.h"

Map::Map()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			rooms[i][j] = new Room(i, j);
		}
	}
	//방 연결
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (i>0) //각 방의 북쪽 방향 연결
			{
				rooms[i][j]->connectRoom(Direction::North, rooms[i - 1][j]);
			}
			if (i < SIZE - 1) //각 방의 남쪽 방향 연결
			{
				rooms[i][j]->connectRoom(Direction::South, rooms[i + 1][j]);
			}
			if (j > 0) //각 방의 서쪽 방향 연결
			{
				rooms[i][j]->connectRoom(Direction::West, rooms[i][j - 1]);
			}
			if (j < SIZE - 1) //각 방의 동쪽 방향 연결
			{
				rooms[i][j]->connectRoom(Direction::East, rooms[i][j + 1]);
			}
		}
	}

	//처음엔 임의로 몇개 방 연결 끊기
	rooms[0][0]->connectRoom(Direction::East, nullptr);
	rooms[0][1]->connectRoom(Direction::South, nullptr);
	rooms[1][0]->connectRoom(Direction::South, nullptr);
	rooms[1][1]->connectRoom(Direction::East, nullptr);
	rooms[1][2]->connectRoom(Direction::South, nullptr);
	rooms[1][2]->connectRoom(Direction::East, nullptr);
	rooms[2][0]->connectRoom(Direction::East, nullptr);
	rooms[2][1]->connectRoom(Direction::East, nullptr);
	rooms[2][2]->connectRoom(Direction::East, nullptr);

}

Room* Map::getRoom(int positionX, int positionY)
{
	if (positionX >= 0 && positionX < SIZE && positionY >= 0 && positionY < SIZE)
	{
		return rooms[positionX][positionY];
	}
	else
		return nullptr; //방이 없음.
}

Map::~Map()
{
	//방 메모리 해제
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			delete rooms[i][j];
		}
	}
}
