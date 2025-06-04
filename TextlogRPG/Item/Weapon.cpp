#include "Weapon.h"
#include "../Character/Player.h" 



//void Weapon::ShowItemInfo() const
//{
//	string strItemInfo = "아이템명: " + GetItemInfo().itemName +
//		" ( ATK : " + to_string(GetItemInfo().attack) +
//		", DEF : " + to_string(GetItemInfo().defense) +
//		", AGI : " + to_string(GetItemInfo().agility) + " )";
//
//	Common::PrintSystemMsg(strItemInfo);
//}

//TODO : !!!!!! 반드시 의존역전관계 해결(ITEM클래스들)
void Weapon::EquippedBy(Player* player)
{
	if (player == nullptr) return;
	CharacterStatus status = CharacterStatus::NewStatus(
		GetItemInfo().attack,
		GetItemInfo().defense,
		GetItemInfo().agility
	);

	player->GetCharacterInfo().characterStats = status.AddStatus(status);

	string strUseWeapon = "[System] " + GetItemInfo().itemName + "을(를) 장착합니다.\n";
	Common::PrintSystemMsg(strUseWeapon);
	Common::PauseAndClearScreen();

	player->ShowPlayerStatus();
}
