#include "Armor.h"
#include "../Character/Player.h" 


//void Armor::ShowItemInfo() const
//{
//	string strItemInfo = "아이템명: " + GetItemInfo().itemName +
//		" ( ATK : " + to_string(GetItemInfo().attack) +
//		", DEF : " + to_string(GetItemInfo().defense) +
//		", AGI : " + to_string(GetItemInfo().agility) + " )";
//
//	Common::PrintSystemMsg(strItemInfo);
//}


void Armor::EquippedBy(Player* player)
{
	if (player == nullptr) 
		return;

	CharacterStatus status = CharacterStatus::NewStatus(
		GetItemInfo().attack,
		GetItemInfo().defense,
		GetItemInfo().agility
	);
	player->GetCharacterInfo().characterStats = status.NewStatus(status);

	string strUseArmor = "[System] " + GetItemInfo().itemName + "을(를) 장착합니다.\n";
	Common::PrintSystemMsg(strUseArmor);

	Common::PauseAndClearScreen();

	player->ShowPlayerStatus();
}