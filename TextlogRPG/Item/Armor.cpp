#include "Armor.h"

void Armor::getItemInfo() const
{
	cout << "===== 방어구 정보 =====" << endl;
	cout << "이름: " << getItemName() << endl;
	cout << "방어력: " << getDefense() << endl;
	cout << "민첩성: " << getAgility() << endl;
	cout << "가격: " << getItemCost() << endl;
}


void Armor::Use(Player* player)
{
	//TODO : 방어구 사용 로직 구현
}