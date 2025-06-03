#include "Healer.h"

void Healer::HealPlayer(Player* player, int32_t cost)
{
	if (player->GetPlayerData().playerGold >= cost) 
	{
		int32_t healAmount = player->GetCharacterInfo().iMaxHealth - player->GetCharacterInfo().iCurrentHealth;
		player->Heal(healAmount);
		player->UseGold(cost);

		string strHealMsg = "[System] 힐러 " + npcInfo.npcName + "이(가) 치유를 시작합니다.\n" 
			+ "치유가 진행중입니다....\n"
			+ "치유가 완료되었습니다...\n\n"
			+ player->GetName() + " 님의 체력을 " + to_string(healAmount) + "만큼 회복했습니다.\n"
			+ "치유의 집을 떠나 길거리로 나갑니다..";

		Common::PrintSystemMsg(strHealMsg);
	}
	else 
	{
		Common::PrintSystemMsg("골드가 부족합니다..");
		
	}
	Common::PauseAndClearScreen(5000);
}

void Healer::Interact(Player* player)
{
	if (player == nullptr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. 상호작용을 종료합니다.");
		return;
	}

	Common::PauseAndClearScreen();

	string strEnterHealerMsg = "치유의 집에 들어갑니다. \n" + npcInfo.npcName + "을(를) 만났습니다.";
	Common::PrintSystemMsg(strEnterHealerMsg);

	string strHealerMsg = "어서오세요! 저는 " + npcInfo.npcName + "입니다.\n"
		+ "당신이 바로 말로만 듣던 바로 그.. " + player->GetName() + " 용사님이군요!\n"
		+ "안색이 좋지 않네요. 치유가 필요하신가요?\n\n"
		+"1. 네, 치유해주세요.(" + to_string(healCost) + "골드)\n2. 아니요, 괜찮습니다.\n";
	Common::PrintSystemMsg(strHealerMsg);

	char healerChoice;
	cin >> healerChoice;
	cin.ignore(1024, '\n');
	Common::PauseAndClearScreen();
	if (healerChoice == '1')
	{
		HealPlayer(player, healCost);
	}
	else if (healerChoice == '2')
	{
		Common::PrintSystemMsg("치유를 거부하셨습니다.\n치유의 집을 떠나 길거리로 나갑니다.");
	}
	else
	{
		Common::PrintSystemMsg("잘못된 선택입니다. 치유의 집을 떠나 길거리로 나갑니다.");;
	}
	Common::PauseAndClearScreen();
	
}

