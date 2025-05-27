#include "MiscItem.h"

void MiscItem::getItemInfo() const
{
	cout << "===== 전리품 정보 =====" << endl;
	cout << "이름: " << getItemName() << endl;
	cout << "가격: " << getItemCost() << endl;
}

void MiscItem::Use(Player* player)
{
	//TODO : 잡템 사용 로직 구현
}