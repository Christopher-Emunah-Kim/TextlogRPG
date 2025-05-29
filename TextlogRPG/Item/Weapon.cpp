#include "Weapon.h"

void Weapon::ShowItemInfo() const
{
	//TODO : 가격빼고 한줄로 표시
	cout << "아이템명: " << GetItemInfo().itemName << "( ATK : " << GetItemInfo().attack << ", DEF : " << GetItemInfo().defense << ", AGI : " << GetItemInfo().agility << " )\n";

}

void Weapon::Use(Player* player)
{
	//TODO : 무기 사용 로직 구현
}
