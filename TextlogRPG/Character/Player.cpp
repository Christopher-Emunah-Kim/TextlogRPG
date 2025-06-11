#include "Player.h"
#include "../Character/CharacterStatus.h"
#include "../Item/Item.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "../LevelData/LevelData.h"

Player::Player(const FPlayerInfo& data)
	: fPlayerInfo(data), m_BaseStatus(data.characterStats), m_EquipmentStatus(CharacterStatus::NewStatus(0, 0, 0))
{
	UpdatePlayerStatus();
}


Player::~Player()
{
}


Player* Player::CreateCharacter(const string& characterName)
{
	FPlayerInfo fTempCharacterInfo;
	return new Player(fTempCharacterInfo);
}

void Player::ApplyDamageFrom(BaseCharacter& target)
{
	const FCharacterInfo& fTargetCharacterInfo = target.GetCharacterInfo();

	int32 iCalculatedDamage = fPlayerInfo.characterStats.CalculateDamage(fTargetCharacterInfo.characterStats);
	
	fPlayerInfo.iCurrentHealth -= iCalculatedDamage;

	if (fPlayerInfo.iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
		fPlayerInfo.iCurrentHealth = 0; // maintain game-over state
	}
	else
	{
		string strDamageText = target.GetCharacterInfo().strCharacterName + "에게 " + to_string(iCalculatedDamage) + "의 데미지를 입었습니다.\n당신의 현재 체력 : " + to_string(fPlayerInfo.iCurrentHealth);
		Common::PrintSystemMsg(strDamageText);
	}
	Common::PauseAndClearScreen(2000);
}

void Player::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	string strAttackText = "당신은 " + target->GetCharacterInfo().strCharacterName + "을(를) 공격합니다.";
	Common::PrintSystemMsg(strAttackText);
	Common::PauseAndClearScreen(3000);

	target->ApplyDamageFrom(*this);
	
}

void Player::SetName(const string& name)
{
	fPlayerInfo.strCharacterName = name;
}

string Player::GetName() const  
{  
    return fPlayerInfo.strCharacterName;
}

FPlayerInfo Player::GetPlayerData() const
{
	return fPlayerInfo;
}


void Player::AddToInventory(Item* item)
{
	m_inventoryManager.AddItem(item);
}


list<Item*> Player::GetInventoryItems(EItemType type) const
{
	return m_inventoryManager.GetItemsByType(type);
}

const EquipmentManager& Player::GetEquipmentManager() const
{
	return m_EquipmentManager;
}



void Player::EquipItem(Item* item)
{
	if (item == nullptr) 
		return;

	//Add previous item to inventory
	Item* previousItem = nullptr;

	switch (item->GetItemInfo().itemType)
	{
	case EItemType::WEAPON:
	{
		previousItem = m_EquipmentManager.GetWeapon();
	}
	break;
	case EItemType::ARMOR:
	{
		previousItem = m_EquipmentManager.GetArmor();
	}
	break;
	case EItemType::MISC:
	{
		//previousItem = m_EquipmentManager.GetMisc();
		//add the misc item to inventory directly
		AddToInventory(item);
		Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 인벤토리에 추가했습니다.");
		Common::PauseAndClearScreen();

		ShowPlayerStatus();
		return;
	}
	break;

	default:
	{
		Common::PrintSystemMsg("기존 장비 정보가 없습니다. 새로운 장비를 장착합니다.");
	}
		break;
	}

	if (previousItem && item->GetItemInfo().itemName == previousItem->GetItemInfo().itemName)
	{
		Common::PrintSystemMsg("동일한 장비를 장착 중입니다: " + item->GetItemInfo().itemName + "\n인벤토리에 아이템이 추가되었습니다.");
	}

	if (previousItem)
	{
		AddToInventory(previousItem);
	}

	m_EquipmentManager.Equip(item);


	UpdateEquipmentStatus();

	UpdatePlayerStatus(); // update status

	Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 장착합니다.");
	Common::PauseAndClearScreen(2000);

	ShowPlayerStatus();

}

void Player::UpdateEquipmentStatus()
{
	int atk = 0, def = 0, agi = 0;
	Weapon* newWeapon = m_EquipmentManager.GetWeapon();
	Armor* newArmor = m_EquipmentManager.GetArmor();
	//MiscItem* newMisc = m_EquipmentManager.GetMisc();

	if (newWeapon)
	{
		atk += newWeapon->GetItemInfo().attack;
		def += newWeapon->GetItemInfo().defense;
		agi += newWeapon->GetItemInfo().agility;
	}

	if (newArmor)
	{
		atk += newArmor->GetItemInfo().attack;
		def += newArmor->GetItemInfo().defense;
		agi += newArmor->GetItemInfo().agility;
	}

	/*if (newMisc)
	{
		atk += newMisc->GetItemInfo().attack;
		def += newMisc->GetItemInfo().defense;
		agi += newMisc->GetItemInfo().agility;
	}*/

	m_EquipmentStatus = CharacterStatus::NewStatus(atk, def, agi);
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) 
		return;
	
	m_inventoryManager.RemoveItem(item);


	//unequip item
	switch (item->GetItemInfo().itemType)
	{
	case EItemType::WEAPON:
	{
		if (m_EquipmentManager.GetWeapon() == item)
		{
			m_EquipmentManager.Unequip(EItemType::WEAPON);
		}
	}
		break;
	case EItemType::ARMOR:
	{
		if (m_EquipmentManager.GetArmor() == item)
		{
			m_EquipmentManager.Unequip(EItemType::ARMOR);
		}
	}
		break;
	/*case EItemType::MISC:
	{
		if (m_EquipmentManager.GetMisc() == item)
		{
			m_EquipmentManager.Unequip(EItemType::MISC);
		}
	}
		break;*/
	default:
	{
		Common::PrintSystemMsg("해제할 장비가 존재하지 않습니다.");
	}
		break;
	}


	UpdateEquipmentStatus();
	UpdatePlayerStatus();

}

void Player::Heal(int32 healAmount)
{
	if (healAmount <= 0) return;
	fPlayerInfo.iCurrentHealth += healAmount;
	if (fPlayerInfo.iCurrentHealth > fPlayerInfo.iMaxHealth)
	{
		fPlayerInfo.iCurrentHealth = fPlayerInfo.iMaxHealth;
	}
}

void Player::UseGold(int32 cost)
{
	if (cost <= 0) return;
	if (fPlayerInfo.playerGold >= cost)
	{
		fPlayerInfo.playerGold -= cost;
		if (fPlayerInfo.playerGold < 0)
		{
			fPlayerInfo.playerGold = 0; 
		}
	}
}

void Player::EarnGold(int32 earnGold)
{
	if (earnGold <= 0) return;

	fPlayerInfo.playerGold += earnGold;
	string strEarnGoldMsg = to_string(earnGold) + " 골드를 획득했습니다. 현재 골드: " + to_string(fPlayerInfo.playerGold);
	Common::PrintSystemMsg(strEarnGoldMsg);
}

void Player::GainLoot(int32 experience, int32 gold, Item* item)
{
	if (experience < 0 || gold < 0) return;

	fPlayerInfo.playerExperience += experience;
	fPlayerInfo.playerGold += gold;

	Common::PrintLine();
	Common::PrintSystemMsg("최종 전투 결과입니다!!\n당신은 "+ to_string(experience) + " 경험치와 " + to_string(gold) + " 골드를 획득했습니다.");
	if (item != nullptr)
	{
		//AddToInventory(item);
		Common::PrintSystemMsg("아이템 " + item->GetItemInfo().itemName + "을(를) 획득했습니다.");
	}
	Common::PrintLine();


	Common::PauseAndClearScreen();

	ShowPlayerStatus();

    while (fPlayerInfo.playerExperience >= fPlayerInfo.playerMaxExperience)
	{
		//experience carry-over delete
		fPlayerInfo.playerExperience -= fPlayerInfo.playerMaxExperience;
		CharacterLevelUp();
	}
}

void Player::UpdatePlayerStatus()
{
	fPlayerInfo.characterStats = CharacterStatus::NewStatus(
		m_BaseStatus.GetAttack() + m_EquipmentStatus.GetAttack(),
		m_BaseStatus.GetDefense() + m_EquipmentStatus.GetDefense(),
		m_BaseStatus.GetAgility() + m_EquipmentStatus.GetAgility()
	);
}

BaseCharacter& Player::CharacterLevelUp()
{
	//Update Player's level and status based on LevelData Array
	fPlayerInfo.iCurrentLevel++;
	if (fPlayerInfo.iCurrentLevel > DEFAULT_CHARACTER_MAX_LEVEL)
	{
		fPlayerInfo.iCurrentLevel = DEFAULT_CHARACTER_MAX_LEVEL; 
		return *this;
	}

	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(fPlayerInfo.iCurrentLevel);

	fPlayerInfo.iMaxHealth = levelData.maxHealthPerLevel;
	fPlayerInfo.playerMaxExperience = levelData.maxExperiencePerLevel;
	fPlayerInfo.iCurrentHealth = fPlayerInfo.iMaxHealth; // Reset current health to max health after level up

	// additional status reward
	Common::PrintSystemMsg("레벨업!\n추가로 올릴 능력치를 선택하세요 : \n\n1.공격력을 추가로 획득한다.\n2.방어력을 추가로 획득한다.\n3.민첩성을 추가로 획득한다.");
	char statusChoice = Common::GetCharInput();
	int16 playerAtk = levelData.attackPerLevel;
	int16 playerDef = levelData.defensePerLevel;
	int16 playerAgi = levelData.agilityPerLevel;
	switch (statusChoice)
	{
	case '1':
		playerAtk += LEVELUP_BONUS;
		break;
	case '2':
		playerDef += LEVELUP_BONUS;
		break;
	case '3':
		playerAgi += LEVELUP_BONUS;
		break;

	default :
		break;
	}

	// Update character stats based on level data
	m_BaseStatus = CharacterStatus::NewStatus(playerAtk, playerDef, playerAgi);

	UpdatePlayerStatus();

	Common::PauseAndClearScreen(300);

	string strLevelUpMsg = "레벨업 결과 보기\n현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n"
		+ "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility());

	Common::PrintSystemMsg(strLevelUpMsg);
	return *this; 
}

void Player::ShowPlayerStatus() const
{
	string strWeaponName, strArmorName;

	Weapon* equippedWeapon = m_EquipmentManager.GetWeapon();
	Armor* equipppedArmor = m_EquipmentManager.GetArmor();
	//MiscItem* ownedMiscItem = m_EquipmentManager.GetMisc();

	if (equippedWeapon)
	{
		strWeaponName = equippedWeapon->GetItemName();
	}
	else
	{
		strWeaponName = "비어있음";
	}

	if (equipppedArmor)
	{
		strArmorName = equipppedArmor->GetItemName();
	}
	else
	{
		strArmorName = "비어있음";
	}

	/*if (ownedMiscItem)
	{
		strMiscItemName = ownedMiscItem->GetItemName();
	}*/
	/*else
	{
		strMiscItemName = "비어있음";
	}*/
	

	string strPlayerStatus = GetName() + " 용사의 스테이터스\n"
		+ "현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "경험치 : " + to_string(fPlayerInfo.playerExperience) + "/" + to_string(fPlayerInfo.playerMaxExperience) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n\n"
		+ "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility()) + "\n\n"
		+ "장착 중인 무기 : " + strWeaponName + "\n"
		+ "장착 중인 방어구 : " + strArmorName + "\n"
		+ "보유 금화 : " + to_string(fPlayerInfo.playerGold) + "\n";

	const list<Item*>& inventoryItems = m_inventoryManager.GetAllItems();
	strPlayerStatus += "\n인벤토리 아이템 목록 : ";
	if (inventoryItems.empty())
	{
		strPlayerStatus += "(비어있음)\n";
	}
	else
	{
		for (list<Item*>::const_iterator it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
		{
			Item* item = *it;
			strPlayerStatus += " [ " + item->GetItemInfo().itemName + " ], ";
		}
	}


	Common::PrintSystemMsg(strPlayerStatus);

	Common::PauseAndClearScreen(3000);
}

