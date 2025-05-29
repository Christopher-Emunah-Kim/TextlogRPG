#include "Armor.h"
#include "../Character/Player.h" 


void Armor::ShowItemInfo() const
{
	cout << "아이템명: " << GetItemInfo().itemName << "( ATK : " << GetItemInfo().attack << ", DEF : " << GetItemInfo().defense << ", AGI : " << GetItemInfo().agility << " )\n";
}


void Armor::Use(Player* player)
{
	if (player == nullptr) return;
	CharacterStatus status = CharacterStatus::NewStatus(
		GetItemInfo().attack,
		GetItemInfo().defense,
		GetItemInfo().agility
	);
	player->GetCharacterInfo().characterStats = status.NewStatus(status);
	cout << "\n===========================================\n" << endl;
	cout << "[System] " << GetItemInfo().itemName << "을(를) 장착했습니다." << endl;
	cout << "\n===========================================\n" << endl;

}