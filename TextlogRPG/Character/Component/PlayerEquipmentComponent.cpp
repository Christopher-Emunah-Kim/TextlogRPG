#include "PlayerEquipmentComponent.h"
#include "PlayerStatusComponent.h"
#include "../Player.h"
#include "../../Item/Item.h"
#include "../../Item/Weapon.h"
#include "../../Item/Armor.h"

PlayerEquipmentComponent::PlayerEquipmentComponent(Player* owner)
    : m_owner(owner), m_equipmentStatus(CharacterStatus::NewStatus(0, 0, 0))
{
}

void PlayerEquipmentComponent::Initialize()
{
	m_equipmentStatus = CharacterStatus::NewStatus(0, 0, 0);
}

void PlayerEquipmentComponent::Update()
{
   
}

void PlayerEquipmentComponent::SetOwner(Player* owner)
{
	m_owner = owner;
}

void PlayerEquipmentComponent::EquipItem(Item* item)
{
    if (item == nullptr) 
        return;

	//add the misc item to inventory directly
    if (item->GetItemInfo().itemType == EItemType::MISC)
    {
        HandleMiscItem(item);
        return;
    }

	//Add previous item to inventory
    Item* previousItem = HandlePreviousEquipItem(item);
    
	//perform equip process
    UpdateEquipItem(previousItem, item);
    
    UpdateEquipmentStatus();

	//m_owner->UpdateFinalStatus();

	PlayerStatusComponent statuscomp = m_owner->GetStatusComponent();

	statuscomp.UpdateFinalStatus();
    
    //Render the results
    RenderEquipMessage(item);
	m_owner->RenderPlayerStatus();
}

void PlayerEquipmentComponent::UnequipItem(Item* item)
{
    if (item == nullptr)
        return;

    EItemType itemType = item->GetItemInfo().itemType;
    
    if (m_equipmentManager.HasEquippedItem(itemType))
    {
        if (m_equipmentManager.GetEquippedItem(itemType))
        {
			m_equipmentManager.Unequip(itemType);
        }
    }
}

void PlayerEquipmentComponent::UpdateEquipmentStatus()
{
    int atk = 0, def = 0, agi = 0;

    if (m_equipmentManager.HasEquippedItem(EItemType::WEAPON))
    {
        Weapon* newWeapon = m_equipmentManager.GetWeapon();
        atk += newWeapon->GetItemInfo().attack;
        def += newWeapon->GetItemInfo().defense;
        agi += newWeapon->GetItemInfo().agility;
    }

    if (m_equipmentManager.HasEquippedItem(EItemType::ARMOR))
    {
        Armor* newArmor = m_equipmentManager.GetArmor();
        atk += newArmor->GetItemInfo().attack;
        def += newArmor->GetItemInfo().defense;
        agi += newArmor->GetItemInfo().agility;
    }

	m_equipmentStatus = CharacterStatus::NewStatus(atk, def, agi);
}

Item* PlayerEquipmentComponent::HandlePreviousEquipItem(Item* item)
{
    Item* previousItem = nullptr;

    switch (item->GetItemInfo().itemType)
    {
    case EItemType::WEAPON:
        previousItem = m_equipmentManager.GetWeapon();
        break;
    case EItemType::ARMOR:
        previousItem = m_equipmentManager.GetArmor();
        break;
    default:
        Common::PrintSystemMsg("기존 장비 정보가 없습니다. 새로운 장비를 장착합니다.");
        break;
    }

    if (previousItem && item->GetItemInfo().itemName == previousItem->GetItemInfo().itemName)
    {
        Common::PrintSystemMsg("동일한 장비를 장착 중입니다: " + item->GetItemInfo().itemName + 
                              "\n인벤토리에 아이템이 추가되었습니다.");
    }

    return previousItem;
}

void PlayerEquipmentComponent::HandleMiscItem(Item* item)
{
	m_owner->AddToInventory(item);
    RenderMiscItemAdded(item);
	m_owner->RenderPlayerStatus();
}

const EquipmentManager& PlayerEquipmentComponent::GetEquipmentManager() const
{
    return m_equipmentManager;
}

void PlayerEquipmentComponent::RenderEquipMessage(Item* newItem)
{
    Common::PrintSystemMsg(newItem->GetItemInfo().itemName + "을(를) 장착합니다.");
    Common::PauseAndClearScreen(2000);
}

void PlayerEquipmentComponent::RenderMiscItemAdded(Item* item)
{
    Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 인벤토리에 추가했습니다.");
    Common::PauseAndClearScreen();
}

void PlayerEquipmentComponent::UpdateEquipItem(Item* previousItem, Item* newItem)
{
    if (previousItem)
    {
		m_owner->AddToInventory(previousItem);
    }

	m_equipmentManager.Equip(newItem);
}