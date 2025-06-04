#include "Weapon.h"
#include "../Character/Player.h" 





//TODO : !!!!!! 반드시 의존역전관계 해결(ITEM클래스들)
void Weapon::EquippedBy(Player* player)
{
	/*if (player == nullptr) return;
	CharacterStatus status = CharacterStatus::NewStatus(
		GetItemInfo().attack,
		GetItemInfo().defense,
		GetItemInfo().agility
	);

	player->GetCharacterInfo().characterStats = status.AddStatus(status);*/

}
