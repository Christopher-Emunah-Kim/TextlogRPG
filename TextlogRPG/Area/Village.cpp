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
	: m_healerNPC(nullptr), m_merchantNPC(nullptr)
{

}


Village::~Village()
{
	Clear();
}



void Village::Enter(Player* player)
{
	m_player = player;
	m_villageState = EVillageState::MAIN_MENU;
	m_isInteractingWithNPC = false;
	m_currentNPC = nullptr;

	RenderVillagePrompt();
}


void Village::ProcessInput(Player* player)
{
	if (m_villageState == EVillageState::MAIN_MENU && !m_isInteractingWithNPC)
	{
		m_input = Common::GetCharInput();
	}
}

void Village::Update(float deltaTime)
{
	m_accumulatedTime += deltaTime;

	if (m_input != 0 && m_villageState == EVillageState::MAIN_MENU)
	{
		switch (m_input)
		{
		case '1':
		{
			if (m_healerNPC)
			{
				m_isInteractingWithNPC = true;
				m_currentNPC = m_healerNPC;
				InteractWithNPC(m_player, m_healerNPC);
				m_isInteractingWithNPC = false;
			}
		}
			break;

		case '2':
		{
			if (m_merchantNPC)
			{
				m_isInteractingWithNPC = true;
				m_currentNPC = m_merchantNPC;
				InteractWithNPC(m_player, m_merchantNPC);
				m_isInteractingWithNPC = false;
			}
		}
			break;

		case '3':
		{
			Common::PrintSystemMsg("타이틀로 돌아갑니다.");
			Common::PauseAndClearScreen();
			m_nextState = EGameState::TITLE;
			m_isRunning = false;
			m_input = 0;
			return;
		}
			break;

		default:
		{
			Common::PrintErrorMsg("잘못된 입력입니다.");
		}
			break;
		}

		// 초기화
		m_input = 0;
	}

	// clear after interaction
	if (!m_isInteractingWithNPC && m_accumulatedTime > 0.5f)
	{
		if (m_villageState != EVillageState::MAIN_MENU)
		{
			m_villageState = EVillageState::MAIN_MENU;
			Common::PauseAndClearScreen();
			RenderVillagePrompt();
		}
		m_accumulatedTime = 0.0f;
	}
}

void Village::Render()
{
	if (!m_isRunning)
		return;

	if (m_villageState == EVillageState::MAIN_MENU && !m_isInteractingWithNPC)
	{
		RenderVillagePrompt();
	}
}

bool Village::ShouldExit()
{
	return !m_isRunning;
}

EGameState Village::GetNextState()
{
	return m_nextState;
}

void Village::RenderVillagePrompt()
{
	Common::PrintSystemMsg("마을로 이동합니다..");
	Common::PauseAndClearScreen();
	Common::PrintSystemMsg("마을에 도착했습니다. \n\n1. 힐러 만나기\n2. 상인 만나기\n3. 마을 나가기");
}

void Village::Initialize(Player* player)
{
	if (m_healerNPC == nullptr)
	{
		m_healerNPC = new Healer("성녀 마리아", DEFAULT_HEAL_COST);
		AddNPC(m_healerNPC);
	}

	if (m_merchantNPC == nullptr)
	{
		m_merchantNPC = new Merchant("대장장이 빌");
		AddNPC(m_merchantNPC);

		//Add Selling Items to Merchant
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
				m_merchantNPC->AddItemForSale(itemName, itemPrice);
			}
		}
	}
}

EGameState Village::Process(Player* player)
{
	/*Enter(player);

	char villageChoice = Common::GetCharInput();

	Common::PauseAndClearScreen();

	return HandleChoice(villageChoice, player);*/

	return Run(player);
}



void Village::Clear()
{
	for (vector<NonPlayerCharacter*>::iterator it = vecNpcCharacters.begin(); it != vecNpcCharacters.end(); ++it)
	{
		NonPlayerCharacter* npc = *it;
		if (npc)
		{
			delete npc;
		}
	}
	vecNpcCharacters.clear();

	m_healerNPC = nullptr;
	m_merchantNPC = nullptr;
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
		InteractWithNPC(player, m_healerNPC);
		return EGameState::VILLAGE;
	}break;
	case '2':
	{
		InteractWithNPC(player, m_merchantNPC);
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
