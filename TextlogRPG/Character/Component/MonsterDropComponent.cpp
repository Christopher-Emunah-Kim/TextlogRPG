#include "MonsterDropComponent.h"
#include "../Monster.h"
#include "../Player.h"
#include "../../Item/Item.h"
#include "../../Core/ItemManager.h"

MonsterDropComponent::MonsterDropComponent(Monster* owner)
	: m_owner(owner), m_lastDropItem(nullptr), m_dropExperience(0), m_dropGold(0)
{
}

MonsterDropComponent::~MonsterDropComponent()
{
}

void MonsterDropComponent::Initialize()
{
    m_lastDropItem = nullptr;
}

void MonsterDropComponent::Update()
{
}

void MonsterDropComponent::SetOwner(BaseCharacter* owner)
{
    m_owner = dynamic_cast<Monster*>(owner);
}

void MonsterDropComponent::InitializeDropItems(const vector<string>& itemNames)
{
    m_dropItemNames = itemNames;
}

void MonsterDropComponent::SetDropValues(int32 experience, int32 gold)
{
	m_dropExperience = experience;
	m_dropGold = gold;
}

bool MonsterDropComponent::ProcessItemDrop(Player* playerTarget)
{
    if (m_owner == nullptr || m_dropItemNames.empty())
    {
        return false;
    }

    srand(static_cast<unsigned int>(time(NULL)));
    size_t randomIndex = rand() % m_dropItemNames.size();

    string strRandomItemName = m_dropItemNames[randomIndex];

    m_lastDropItem = ItemManager::GetInstance().CreateItem(strRandomItemName);

    return (m_lastDropItem != nullptr);
}

void MonsterDropComponent::RenderItemDropResult(Item* droppedItem, bool isSuccessful, Player* attacker)
{
    if (isSuccessful == false || droppedItem == nullptr)
    {
        Common::PrintSystemMsg("아이템 드랍을 실패했습니다.");
        return;
    }

    Common::PrintSystemMsg("전리품을 획득했습니다!");
    droppedItem->ShowItemInfo();


    Common::PrintSystemMsg("이 아이템을 등록하시겠습니까?\n-> 1. 새로운 아이템을 등록한다.  2. 기존의 아이템을 사용한다.");
    char equipChoice = Common::GetCharInput();

    Player* playerTarget = dynamic_cast<Player*>(attacker);

    if (playerTarget == nullptr) 
        return;

    if (equipChoice == '1')
    {
        playerTarget->EquipItem(droppedItem);
    }
    else if (equipChoice == '2')
    {
        playerTarget->AddToInventory(droppedItem);
        Common::PrintSystemMsg("아이템을 인벤토리에 보관했습니다.");
    }
    else
    {
        Common::PrintSystemMsg("잘못된 입력입니다. 아이템을 획득하지 못했습니다.");
        return;
    }

    playerTarget->GainLoot(m_dropExperience, m_dropGold, droppedItem);
}

