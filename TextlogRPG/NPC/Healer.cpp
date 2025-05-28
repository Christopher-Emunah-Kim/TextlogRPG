#include "Healer.h"

void Healer::HealPlayer(Player* player, int32_t cost)
{
	if (player->GetPlayerData().playerGold >= cost) {
		int32_t healAmount = player->GetCharacterInfo().maxHealth - player->GetCharacterInfo().health;
		player->Heal(healAmount);
		player->UseGold(cost);
		cout << "[System] " << healAmount << "의 체력을 회복했습니다." << endl;
	}
	else {
		cout << "[System] 골드가 부족합니다." << endl;
	}
}

void Healer::Interact(Player* player)
{
	cout << "[System] 힐러 " << npcName << "와 상호작용합니다." << endl;
	HealPlayer(player, healCost);
}
