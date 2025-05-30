#include "Village.h"
#include "../NPC/NonPlayerCharacter.h"

void Village::Enter(Player* player)
{
	cout << "\n===========================================\n";
	cout << "\n[System] 마을로 이동합니다...\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n";
	cout << "\n[System] 마을에 도착했습니다.\n";
	cout << "\n1. 힐러 만나기\n2. 상인 만나기\n3. 마을 나가기\n";
	cout << "\n===========================================\n" << endl;
}


void Village::AddNPC(NonPlayerCharacter* npc) 
{
	npcCharacters.push_back(npc);
}

void Village::RemoveNPC(NonPlayerCharacter* npc) 
{
	npcCharacters.erase(remove(npcCharacters.begin(), npcCharacters.end(), npc), npcCharacters.end());
}

vector<NonPlayerCharacter*>& Village::GetNPCList()
{
	return npcCharacters;
}

void Village::InteractWithNPC(Player* player, NonPlayerCharacter* npc)
{
	//TODO : <int32_t, vector<NonPlayerCharacter*>> map을 만들어서 입력한 num에 따라 필요한 interact를 발동하도록 하는게 나을듯.
	if (npc) 
		npc->Interact(player);
}