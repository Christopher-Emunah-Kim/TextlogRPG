#include "Player.h"
#include "../Character/CharacterStatus.h"
#include "../Item/Item.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"
#include "../LevelData/LevelData.h"


Player* Player::CreateCharacter(const string& characterName)
{
	//TODO : 임시_이후 LevelData 연결
	FPlayerInfo fTempCharacterInfo = { CharacterStatus::NewStatus(12, 9, 8), 25, 25, 1, characterName };

	return new Player(fTempCharacterInfo);
}

void Player::ReceiveDamageFrom(BaseCharacter& target)
{
	const FCharacterInfo& fTargetCharacterInfo = target.GetCharacterInfo();

	int32 iCalculatedDamage = fPlayerInfo.characterStats.CalculateDamage(fTargetCharacterInfo.characterStats);
	
	fPlayerInfo.iCurrentHealth -= iCalculatedDamage;

	if (fPlayerInfo.iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
		fPlayerInfo.iCurrentHealth = 0; // maintain gameover state with zero health
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

	target->ReceiveDamageFrom(*this);
	
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

	/*if (item == nullptr)
		return;

	vector<Item*>::iterator it = find(m_playerInventory.begin(), m_playerInventory.end(), item);
	if (it == m_playerInventory.end()) {
		m_playerInventory.push_back(item);
	}
	else {
		Common::PrintSystemMsg("이미 보유 중인 아이템입니다.");
	}*/
}

vector<Item*> Player::GetInventoryItems(EItemType type) const
{
	return m_inventoryManager.GetItemsByType(type);

	/*vector<Item*> itemListByType;

	for (size_t i = 0; i < m_playerInventory.size(); ++i) 
	{
		Item* item = m_playerInventory[i];
		if (item->GetItemInfo().itemType == type)
		{
			itemListByType.push_back(item);
		}
	}
	return itemListByType;*/
}



void Player::EquipItem(Item* item)
{
	if (item == nullptr) 
		return;

	// add previous item to inventory 
	if(item->GetItemInfo().itemType== EItemType::WEAPON && fPlayerInfo.weaponEquipped != nullptr) 
	{
		AddToInventory(fPlayerInfo.weaponEquipped);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR && fPlayerInfo.armorEquipped != nullptr)
	{
		AddToInventory(fPlayerInfo.armorEquipped);
	}

	// update new equipment
	if (item->GetItemInfo().itemType == EItemType::WEAPON) {
		fPlayerInfo.weaponEquipped = dynamic_cast<Weapon*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR) {
		fPlayerInfo.armorEquipped = dynamic_cast<Armor*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::MISC)
	{
		fPlayerInfo.miscOwned = dynamic_cast<MiscItem*>(item);
	}


	UpdateEquipmentStatus();

	UpdatePlayerStatus(); // update status

	Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 장착합니다.");
	Common::PauseAndClearScreen(2000);

	ShowPlayerStatus();

}

void Player::UpdateEquipmentStatus()
{
	int atk = 0, def = 0, agi = 0;
	if (fPlayerInfo.weaponEquipped)
	{
		atk += fPlayerInfo.weaponEquipped->GetItemInfo().attack;
		def += fPlayerInfo.weaponEquipped->GetItemInfo().defense;
		agi += fPlayerInfo.weaponEquipped->GetItemInfo().agility;
	}
	if (fPlayerInfo.armorEquipped)
	{
		atk += fPlayerInfo.armorEquipped->GetItemInfo().attack;
		def += fPlayerInfo.armorEquipped->GetItemInfo().defense;
		agi += fPlayerInfo.armorEquipped->GetItemInfo().agility;
	}
	if (fPlayerInfo.miscOwned)
	{
		atk += fPlayerInfo.miscOwned->GetItemInfo().attack;
		def += fPlayerInfo.miscOwned->GetItemInfo().defense;
		agi += fPlayerInfo.miscOwned->GetItemInfo().agility;
	}
	m_EquipmentStatus = CharacterStatus::NewStatus(atk, def, agi);
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) 
		return;
	
	m_inventoryManager.RemoveItem(item);

	/*vector<Item*>::iterator it = find(m_playerInventory.begin(), m_playerInventory.end(), item);
	if (it != m_playerInventory.end())
	{
		m_playerInventory.erase(it);
	}*/

	switch (item->GetItemInfo().itemType)
	{
	case EItemType::WEAPON:
	{
		if (fPlayerInfo.weaponEquipped == item)
		{
			fPlayerInfo.weaponEquipped = nullptr;
		}
	}
	break;
	case EItemType::ARMOR:
	{
		if (fPlayerInfo.armorEquipped == item)
		{
			fPlayerInfo.armorEquipped = nullptr;
		}
	}
	break;
	case EItemType::MISC:
	{
		if (fPlayerInfo.miscOwned == item)
		{
			fPlayerInfo.miscOwned = nullptr;
		}
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

	if (fPlayerInfo.playerExperience >= fPlayerInfo.playerMaxExperience)
	{
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
	if (fPlayerInfo.iCurrentLevel > 100)
	{
		fPlayerInfo.iCurrentLevel = 100; // MAX LEVEL
		return *this;
	}

	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(fPlayerInfo.iCurrentLevel);

	fPlayerInfo.iMaxHealth += levelData.maxHealthPerLevel;
	fPlayerInfo.playerMaxExperience += levelData.maxExperiencePerLevel;
	fPlayerInfo.iCurrentHealth = fPlayerInfo.iMaxHealth; // Reset current health to max health after level up

	// additional status reward
	Common::PrintSystemMsg("추가로 올릴 능력치를 선택하세요 : \n\n1.공격력을 추가로 획득한다.\n2.방어력을 추가로 획득한다.\n3.민첩성을 추가로 획득한다.");
	char statusChoice = Common::GetCharInput();
	int16 playerAtk = levelData.attackPerLevel;
	int16 playerDef = levelData.defensePerLevel;
	int16 playerAgi = levelData.agilityPerLevel;
	switch (statusChoice)
	{
	case '1':
		playerAtk += 2;
		break;
	case '2':
		playerDef += 2;
		break;
	case '3':
		playerAgi += 2;
		break;

	default :
		break;
	}

	// Update character stats based on level data
	m_BaseStatus = CharacterStatus::NewStatus(m_BaseStatus.GetAttack() + playerAtk,	m_BaseStatus.GetDefense() + playerDef, m_BaseStatus.GetAgility() + playerAgi	);

	//fPlayerInfo.characterStats = CharacterStatus::NewStatus(playerAtk, playerDef, playerAgi);

	UpdatePlayerStatus();

	string strLevelUpMsg = "레벨업!\n현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n"
		+ "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility());

	Common::PrintSystemMsg(strLevelUpMsg);
	return *this; 
}

void Player::ShowPlayerStatus()
{
	string strWeaponName, strArmorName, strMiscItemName;
	if (fPlayerInfo.weaponEquipped != nullptr)
	{
		strWeaponName = fPlayerInfo.weaponEquipped->GetItemName();
	}
	else
	{
		strWeaponName = "비어있음";
	}
	
	if (fPlayerInfo.armorEquipped != nullptr)
	{
		strArmorName = fPlayerInfo.armorEquipped->GetItemName();
	}
	else
	{
		strArmorName = "비어있음";
	}

	if (fPlayerInfo.miscOwned != nullptr)
	{
		strMiscItemName = fPlayerInfo.miscOwned->GetItemName();
	}
	else
	{
		strMiscItemName = "비어있음";
	}
	

	string strPlayerStatus = GetName() + " 용사의 스테이터스\n"
		+ "현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "경험치 : " + to_string(fPlayerInfo.playerExperience) + "/" + to_string(fPlayerInfo.playerMaxExperience) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n\n"
		+ "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility()) + "\n\n"
		+ "장착 중인 무기 : " + strWeaponName + "\n"
		+ "장착 중인 방어구 : " + strArmorName + "\n"
		+ "보유 중인 아이템 : " + strMiscItemName + "\n\n"
		+ "보유 금화 : " + to_string(fPlayerInfo.playerGold) + "\n";

	Common::PrintSystemMsg(strPlayerStatus);

	Common::PauseAndClearScreen(3500);
}


Player::~Player()
{
	if (fPlayerInfo.weaponEquipped != nullptr)
	{
		delete fPlayerInfo.weaponEquipped;
		fPlayerInfo.weaponEquipped = nullptr;
	}
	if (fPlayerInfo.armorEquipped != nullptr)
	{
		delete fPlayerInfo.armorEquipped;
		fPlayerInfo.armorEquipped = nullptr;
	}
	if (fPlayerInfo.miscOwned != nullptr)
	{
		delete fPlayerInfo.miscOwned;
		fPlayerInfo.miscOwned = nullptr;
	}
	for (size_t i = 0; i<m_playerInventory.size(); ++i)
	{
		Item* item = m_playerInventory[i];
		delete item;
	}
	m_playerInventory.clear();
	
}
