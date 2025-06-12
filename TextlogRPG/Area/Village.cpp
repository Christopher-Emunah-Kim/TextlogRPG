#include "Village.h"
#include "../NPC/NonPlayerCharacter.h"
#include "../NPC/Healer.h"
#include "../NPC/Merchant.h"
#include "../Character/Player.h"
#include "../Core/ItemManager.h"
#include "../Item/Item.h"
#include "../Util/EGameState.h"
#include "../Core/GameManager.h"

Village::Village()
	: healerNPC(nullptr), merchantNPC(nullptr)
{

}

Village::~Village()
{
	Clear();
}



void Village::Enter(Player* player)
{
	RenderVillagePrompt();
}

void Village::RenderVillagePrompt()
{
	Common::PrintSystemMsg("마을로 이동합니다..");
	Common::PauseAndClearScreen();
	Common::PrintSystemMsg("마을에 도착했습니다. \n\n1. 힐러 만나기\n2. 상인 만나기\n3. 마을 나가기");
}

void Village::Initialize(Player* player)
{
	healerNPC = new Healer("성녀 마리아", DEFAULT_HEAL_COST);
	merchantNPC = new Merchant("대장장이 빌");

	AddNPC(healerNPC);
	AddNPC(merchantNPC);

	ItemManager& itemManager = ItemManager::GetInstance();
	vector<string> items = itemManager.GetItemList();

	for (size_t i = 0; i < items.size(); ++i)
	{
		const string& itemName = items[i];
		Item* item = itemManager.GetItem(itemName);
		if (item == nullptr)
			continue;

		EItemType itemType = item->GetItemInfo().itemType;
		int32 itemPrice = item->GetItemInfo().itemCost;

		if (itemType == EItemType::WEAPON || itemType == EItemType::ARMOR || itemType == EItemType::MISC)
		{
			merchantNPC->AddItemForSale(itemName, itemPrice);
		}
	}
}

EGameState Village::Process(Player* player)
{
	Enter(player);

	char villageChoice = Common::GetCharInput();

	Common::PauseAndClearScreen();

	return HandleChoice(villageChoice, player);
}



void Village::Clear()
{
	if (healerNPC != nullptr)
	{
		RemoveNPC(healerNPC);
		delete healerNPC;
		healerNPC = nullptr;
	}

	if (merchantNPC != nullptr)
	{
		RemoveNPC(merchantNPC);
		delete merchantNPC;
		merchantNPC = nullptr;
	}

	vecNpcCharacters.clear();
}

void Village::AddNPC(NonPlayerCharacter* npc) 
{
	if (npc != nullptr)
	{
		vecNpcCharacters.push_back(npc);
	}
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

EGameState Village::HandleChoice(char villageChoice, Player* player)
{
	switch (villageChoice)
	{
	case '1':
	{
		InteractWithNPC(player, healerNPC);
		return EGameState::VILLAGE;
	}break;
	case '2':
	{
		InteractWithNPC(player, merchantNPC);
		return EGameState::VILLAGE;
	}break;
	case '3':
	{
		return EGameState::TITLE;
	}break;

	default:
	{
		Common::PrintErrorMsg("잘못된 입력입니다.");
		return EGameState::VILLAGE;
	}
	}
}
