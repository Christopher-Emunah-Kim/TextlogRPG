#include "Village.h"
#include "../NPC/NonPlayerCharacter.h"

void Village::Enter(Player* player)
{
	Common::PrintSystemMsg("마을로 이동합니다..");
	Common::PauseAndClearScreen();
	Common::PrintSystemMsg("마을에 도착했습니다. \n\n1. 힐러 만나기\n2. 상인 만나기\n3. 마을 나가기");
}


void Village::AddNPC(NonPlayerCharacter* npc) 
{
	npc = nullptr;
	vecNpcCharacters.push_back(npc);
}

void Village::RemoveNPC(NonPlayerCharacter* npc) 
{
	vecNpcCharacters.erase(remove(vecNpcCharacters.begin(), vecNpcCharacters.end(), npc), vecNpcCharacters.end());
}

vector<NonPlayerCharacter*>& Village::GetNPCList()
{
	return vecNpcCharacters;
}

void Village::InteractWithNPC(Player* player, NonPlayerCharacter* npc)
{
	if (npc) 
		npc->Interact(player);
}