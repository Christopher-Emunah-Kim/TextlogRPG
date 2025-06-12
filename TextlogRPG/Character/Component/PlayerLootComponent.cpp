#include "PlayerLootComponent.h"
#include "../Player.h"
#include "../../Item/Item.h"

PlayerLootComponent::PlayerLootComponent(Player* owner)
    : m_owner(owner)
{
}

void PlayerLootComponent::Initialize()
{
}

void PlayerLootComponent::Update()
{
}

void PlayerLootComponent::SetOwner(Player* owner)
{
	m_owner = owner;
}

void PlayerLootComponent::AddGold(int32 gold)
{
    if (gold < 0)
        return;
	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
	playerInfo.playerGold += gold;
}

void PlayerLootComponent::UseGold(int32 cost)
{
    if (cost <= 0)
        return;

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    if (playerInfo.playerGold >= cost)
    {
        playerInfo.playerGold -= cost;

        if (playerInfo.playerGold < 0)
            playerInfo.playerGold = 0;
    }
}

void PlayerLootComponent::EarnGold(int32 earnGold)
{
    UpdateGold(earnGold);
    RenderGoldChange(earnGold);
}

void PlayerLootComponent::GainLoot(int32 experience, int32 gold, Item* item)
{
    UpdateLoot(gold, experience);
    RenderLootResult(experience, gold, item);
}

void PlayerLootComponent::AddExperience(int32 experience)
{
    if (experience <= 0)
        return;

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
	playerInfo.playerExperience += experience;
}

void PlayerLootComponent::ProcessLevelUp()
{
    FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    while (playerInfo.playerExperience >= playerInfo.playerMaxExperience)
    {
        // 초과 경험치 이월
        playerInfo.playerExperience -= playerInfo.playerMaxExperience;
		m_owner->CharacterLevelUp();
    }
}

void PlayerLootComponent::UpdateLoot(int32 gold, int32 experience)
{
    AddGold(gold);
    AddExperience(experience);
    ProcessLevelUp();
}

void PlayerLootComponent::UpdateGold(int32 earnGold)
{
    if (earnGold <= 0)
        return;

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
	playerInfo.playerGold += earnGold;
}

void PlayerLootComponent::RenderGoldChange(int32 earnGold)
{
    string strEarnGoldMsg = to_string(earnGold) + " 골드를 획득했습니다. 현재 골드: " + 
                           to_string(m_owner->GetCharacterInfo().playerGold);
    Common::PrintSystemMsg(strEarnGoldMsg);
}

void PlayerLootComponent::RenderLootResult(int32 experience, int32 gold, Item* item)
{
    Common::PrintLine();
    Common::PrintSystemMsg("최종 전투 결과입니다!!\n당신은 " + to_string(experience) + 
                         " 경험치와 " + to_string(gold) + " 골드를 획득했습니다.");
    
    if (item != nullptr)
    {
        Common::PrintSystemMsg("아이템 " + item->GetItemInfo().itemName + "을(를) 획득했습니다.");
    }
    
    Common::PrintLine();
    Common::PauseAndClearScreen();

	m_owner->RenderPlayerStatus();
}