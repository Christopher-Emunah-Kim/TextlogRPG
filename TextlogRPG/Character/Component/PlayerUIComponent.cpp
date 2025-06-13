#include "PlayerUIComponent.h"
#include "../Player.h"
#include "../../Item/Item.h"
#include "../../Item/Weapon.h"
#include "../../Item/Armor.h"

PlayerUIComponent::PlayerUIComponent(Player* owner)
    : m_owner(owner)
{
}

void PlayerUIComponent::Initialize()
{
}

void PlayerUIComponent::Update()
{
}

void PlayerUIComponent::SetOwner(BaseCharacter* owner)
{
	m_owner = dynamic_cast<Player*>(owner);
}

void PlayerUIComponent::RenderPlayerStatus() const
{
	Common::PauseAndClearScreen(500);
    string statusString = BuildPlayerStatusString();
    Common::PrintSystemMsg(statusString);
    Common::PauseAndClearScreen(2000);
}

string PlayerUIComponent::BuildPlayerStatusString() const
{
    string strPlayerStatus = m_owner->GetName() + " 용사의 스테이터스\n";
    strPlayerStatus += BuildBasicInfoString();
    strPlayerStatus += BuildStatsString();
    strPlayerStatus += BuildEquipInfoString();
    strPlayerStatus += BuildInventoryString();
    return strPlayerStatus;
}

string PlayerUIComponent::BuildBasicInfoString() const
{
    const FPlayerInfo& playerInfo = m_owner->GetCharacterInfo();
    return "현재 레벨 : " + to_string(playerInfo.iCurrentLevel) + "\n"
         + "경험치 : " + to_string(playerInfo.playerExperience) + "/" + to_string(playerInfo.playerMaxExperience) + "\n"
         + "체력 : " + to_string(playerInfo.iCurrentHealth) + "/" + to_string(playerInfo.iMaxHealth) + "\n\n";
}

string PlayerUIComponent::BuildStatsString() const
{
    const FPlayerInfo& playerInfo = m_owner->GetCharacterInfo();
    return "공격력 : " + to_string(playerInfo.characterStats.GetAttack()) + "\n"
         + "방어력 : " + to_string(playerInfo.characterStats.GetDefense()) + "\n"
         + "민첩성 : " + to_string(playerInfo.characterStats.GetAgility()) + "\n\n";
}

string PlayerUIComponent::BuildEquipInfoString() const
{
    string strWeaponName, strArmorName;
    const EquipmentManager& equipManager = m_owner->GetEquipmentComponent().GetEquipmentManager();
    
    Weapon* equippedWeapon = equipManager.GetWeapon();
    Armor* equippedArmor = equipManager.GetArmor();

    if (equippedWeapon)
        strWeaponName = equippedWeapon->GetItemName();
    else
        strWeaponName = "비어있음";
    
    if (equippedArmor)
        strArmorName = equippedArmor->GetItemName();
    else
        strArmorName = "비어있음";

    return "장착 중인 무기 : " + strWeaponName + "\n"
         + "장착 중인 방어구 : " + strArmorName + "\n"
         + "보유 금화 : " + to_string(m_owner->GetCharacterInfo().playerGold) + "\n";
}

string PlayerUIComponent::BuildInventoryString() const
{
    string result = "\n인벤토리 아이템 목록 : ";

    const list<Item*>& inventoryItems = m_owner->GetInvetoryComponent().GetAllItems();
    if (inventoryItems.empty())
    {
        result += "(비어있음)\n";
    }
    else
    {
		for (list<Item*>::const_iterator it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
		{
			Item* item = *it;
            result += " [ " + item->GetItemInfo().itemName + " ], ";
        }
    }
    return result;
}