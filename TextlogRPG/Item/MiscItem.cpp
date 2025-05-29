#include "MiscItem.h"

void MiscItem::ShowItemInfo() const
{
	cout << "아이템명: " << GetItemInfo().itemName << "( ATK : " << GetItemInfo().attack << ", DEF : " << GetItemInfo().defense << ", AGI : " << GetItemInfo().agility << " )\n";
}

void MiscItem::Use(Player* player)
{
	//TODO : 잡템 사용 로직 구현
}