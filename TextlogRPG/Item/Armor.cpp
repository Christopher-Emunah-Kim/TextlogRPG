#include "Armor.h"

void Armor::ShowItemInfo() const
{
	cout << "아이템명: " << GetItemInfo().itemName << "( ATK : " << GetItemInfo().attack << ", DEF : " << GetItemInfo().defense << ", AGI : " << GetItemInfo().agility << " )\n";
}


void Armor::Use(Player* player)
{
	//TODO : 방어구 사용 로직 구현
}