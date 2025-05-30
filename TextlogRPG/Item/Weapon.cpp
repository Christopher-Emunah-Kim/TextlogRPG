#include "Weapon.h"
#include "../Character/Player.h" 



void Weapon::ShowItemInfo() const
{
	//TODO : 가격빼고 한줄로 표시
	cout << "아이템명: " << GetItemInfo().itemName << "( ATK : " << GetItemInfo().attack << ", DEF : " << GetItemInfo().defense << ", AGI : " << GetItemInfo().agility << " )\n";

}

void Weapon::Use(Player* player)
{
	if (player == nullptr) return;
	CharacterStatus status = CharacterStatus::NewStatus(
		GetItemInfo().attack,
		GetItemInfo().defense,
		GetItemInfo().agility
	);
	player->GetCharacterInfo().characterStats = status.NewStatus(status);

	cout << "\n===========================================\n";
	cout << "[System] " << GetItemInfo().itemName << "을(를) 장착했습니다.";
	cout << "\n===========================================\n" << endl;

	Sleep(2000);
	system("cls");

	player->ShowPlayerStatus(player);
}
