#include "Weapon.h"

void Weapon::getItemInfo(const string& itemName) const
{
	if (itemName == getItemName())
	{
		cout << "===== 무기 정보 =====" << endl;
		cout << "이름: " << getItemName() << endl;
		cout << "공격력: " << getAttack() << endl;
		cout << "방어력: " << getDefense() << endl;
		cout << "민첩성: " << getAgility() << endl;
		cout << "가격: " << getItemCost() << endl;
	}
}

void Weapon::Use(Player* player)
{
	//TODO : 무기 사용 로직 구현
}
