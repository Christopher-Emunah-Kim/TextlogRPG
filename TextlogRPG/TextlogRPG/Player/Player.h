#pragma once



class Player
{
private :
	//현재 플레이어가 있는 방.
	class Room* currentRoom;
	//플레이어가 이동할 방.
	class Room* targetRoom;

public : 
	//생성자(시작하는 방 정보 초기화)
	Player(class Room* startRoom) : currentRoom(startRoom) {}

	//Direction enum 기준으로 방 이동하기
	// // (이동할 방이 있는지 확인 후 이동)
	// // (이동할 방이 없으면 이동하지 않음)
	void PlayerMove(Direction dir);

	//현재 있는 방 정보 얻는 함수
	inline class Room* getCurrentRoom() const { return currentRoom; }
};

