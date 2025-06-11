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
	Initialize(data);
}


Player::~Player()
{
}


Player* Player::CreateCharacter(const string& characterName)
{
	FPlayerInfo fTempCharacterInfo;
	return new Player(fTempCharacterInfo);
}

void Player::Initialize(const FPlayerInfo& data)
{
	fPlayerInfo = data;
	m_BaseStatus = data.characterStats;
	m_EquipmentStatus = CharacterStatus::NewStatus(0, 0, 0);

	UpdatePlayerStatus();
}


void Player::ApplyDamageFrom(BaseCharacter& attacker)
{
	UpdateDamage(attacker);
	
	RenderDamageResult();
}

void Player::UpdateDamage(BaseCharacter& attacker)
{
	const FCharacterInfo& fTargetCharacterInfo = attacker.GetCharacterInfo();

	int32 iCalculatedDamage = CaculateDamageFrom(fTargetCharacterInfo);

	fPlayerInfo.iCurrentHealth -= iCalculatedDamage;

	if (fPlayerInfo.iCurrentHealth <= 0)
	{
		fPlayerInfo.iCurrentHealth = 0; // maintain game-over state
	}

	m_lastAttacker = &attacker; // Store the last info for reference
	m_lastCalculatedDamage = iCalculatedDamage;
}



void Player::RenderDamageResult()
{
	if (fPlayerInfo.iCurrentHealth <= 0)
	{
		DisplayDeathMessage();

	}
	else
	{
		DisplayDamageMessage(m_lastAttacker, m_lastCalculatedDamage);

	}
	Common::PauseAndClearScreen(2000);
}

void Player::DisplayDeathMessage()
{
	Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
}

void Player::DisplayDamageMessage(BaseCharacter* attacker, int32 damage)
{
	string strDamageText = attacker->GetCharacterInfo().strCharacterName + "에게 " + to_string(damage) + "의 데미지를 입었습니다.\n당신의 현재 체력 : " + to_string(fPlayerInfo.iCurrentHealth);
	Common::PrintSystemMsg(strDamageText);
}



int32 Player::CaculateDamageFrom(const FCharacterInfo& fTargetCharacterInfo)
{
	return fPlayerInfo.characterStats.CalculateDamage(fTargetCharacterInfo.characterStats);
}


void Player::Attack(BaseCharacter* target)
{
	if (target == nullptr)
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
		return;
	}

	RenderAttackMessage(target);

	UpdateAttack(target);
}


void Player::UpdateAttack(BaseCharacter* target)
{
	if (target != nullptr)
	{
		target->ApplyDamageFrom(*this);
	}
	else
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
	}
}

void Player::RenderAttackMessage(BaseCharacter* target)
{
	if (target != nullptr)
	{
		string strAttackText = "당신은 " + target->GetCharacterInfo().strCharacterName + "을(를) 공격합니다.";
		Common::PrintSystemMsg(strAttackText);
		Common::PauseAndClearScreen(2000);
	}
	else
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
		Common::PauseAndClearScreen(1000);
	}
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

	//add the misc item to inventory directly
	if (item->GetItemInfo().itemType == EItemType::MISC)
	{
		HandleMiscItem(item);
		return;
	}

	//Add previous item to inventory
	Item* previousItem = HandlePreviousEquipItem(item);

	//perform equip process
	PerformEquipItem(previousItem, item);
}

void Player::PerformEquipItem(Item* previousItem, Item* newItem)
{
	if (previousItem)
	{
		AddToInventory(previousItem);
	}

	m_EquipmentManager.Equip(newItem);


	UpdateEquipmentStatus();

	UpdatePlayerStatus(); // update status

	Common::PrintSystemMsg(newItem->GetItemInfo().itemName + "을(를) 장착합니다.");
	Common::PauseAndClearScreen(2000);

	RenderPlayerStatus();
}

Item* Player::HandlePreviousEquipItem(Item* item)
{
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

	return previousItem;
}

void Player::HandleMiscItem(Item* item)
{
	AddToInventory(item);
	Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 인벤토리에 추가했습니다.");
	Common::PauseAndClearScreen();

	RenderPlayerStatus();
}

void Player::UpdateEquipmentStatus()
{
	int atk = 0, def = 0, agi = 0;

	if (m_EquipmentManager.HasEquippedItem(EItemType::WEAPON))
	{
		Weapon* newWeapon = m_EquipmentManager.GetWeapon();
		atk += newWeapon->GetItemInfo().attack;
		def += newWeapon->GetItemInfo().defense;
		agi += newWeapon->GetItemInfo().agility;
	}

	if (m_EquipmentManager.HasEquippedItem(EItemType::ARMOR))
	{
		Armor* newArmor = m_EquipmentManager.GetArmor();
		atk += newArmor->GetItemInfo().attack;
		def += newArmor->GetItemInfo().defense;
		agi += newArmor->GetItemInfo().agility;
	}

	m_EquipmentStatus = CharacterStatus::NewStatus(atk, def, agi);
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) 
		return;
	
	RemoveFromInventory(item);

	//unequip item
	UnequipItem(item);

	UpdateEquipmentStatus();

	UpdatePlayerStatus();

}

void Player::UnequipItem(Item* item)
{
	if (item == nullptr)
	{
		return;
	}

	EItemType itemType = item->GetItemInfo().itemType;

	if (m_EquipmentManager.HasEquippedItem(itemType))
	{
		if (m_EquipmentManager.GetEquippedItem(itemType))
		{
			m_EquipmentManager.Unequip(itemType);
		}
	}
}

void Player::RemoveFromInventory(Item* item)
{
	m_inventoryManager.RemoveItem(item);
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
	AddGold(gold);
	AddExperience(experience);

	Common::PrintLine();
	Common::PrintSystemMsg("최종 전투 결과입니다!!\n당신은 "+ to_string(experience) + " 경험치와 " + to_string(gold) + " 골드를 획득했습니다.");
	if (item != nullptr)
	{
		//AddToInventory(item);
		Common::PrintSystemMsg("아이템 " + item->GetItemInfo().itemName + "을(를) 획득했습니다.");
	}
	Common::PrintLine();
	Common::PauseAndClearScreen();

	RenderPlayerStatus();

	ProcessLevelUp();

}

void Player::AddGold(int32 gold)
{
	if (gold < 0)
		return;
	fPlayerInfo.playerGold += gold;
}

void Player::AddExperience(int32 experience)
{
	if (experience <= 0)
		return;
	fPlayerInfo.playerExperience += experience;
}

void Player::ProcessLevelUp()
{
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
	IncrementLevel();


	if (fPlayerInfo.iCurrentLevel > DEFAULT_CHARACTER_MAX_LEVEL)
	{
		fPlayerInfo.iCurrentLevel = DEFAULT_CHARACTER_MAX_LEVEL; 
		return *this;
	}
	
	ApplyLevelDataPerLevel();

	// additional status reward
	ApplyBonusStatus();


	DisplayLevelUpResult();


	return *this; 
}

void Player::DisplayLevelUpResult()
{
	Common::PauseAndClearScreen(300);

	string strLevelUpMsg = "레벨업 결과 보기\n현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n"
		+ "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility());

	Common::PrintSystemMsg(strLevelUpMsg);
}

void Player::ApplyBonusStatus()
{
	Common::PrintSystemMsg("레벨업!\n추가로 올릴 능력치를 선택하세요 : \n\n1.공격력을 추가로 획득한다.\n2.방어력을 추가로 획득한다.\n3.민첩성을 추가로 획득한다.");
	char statusChoice = Common::GetCharInput();

	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(fPlayerInfo.iCurrentLevel);
	int16 playerAtk = levelData.attackPerLevel;
	int16 playerDef = levelData.defensePerLevel;
	int16 playerAgi = levelData.agilityPerLevel;

	ApplyStatusBonus(statusChoice, playerAtk, playerDef, playerAgi);

	// Update character stats based on level data
	m_BaseStatus = CharacterStatus::NewStatus(playerAtk, playerDef, playerAgi);

	UpdatePlayerStatus();
}

void Player::ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi)
{
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

	default:
		break;
	}
}

void Player::IncrementLevel()
{
	fPlayerInfo.iCurrentLevel++;
}

void Player::ApplyLevelDataPerLevel()
{
	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(fPlayerInfo.iCurrentLevel);
	fPlayerInfo.iMaxHealth = levelData.maxHealthPerLevel;
	fPlayerInfo.playerMaxExperience = levelData.maxExperiencePerLevel;
	fPlayerInfo.iCurrentHealth = fPlayerInfo.iMaxHealth; // Reset current health to max health after level up
}

void Player::RenderPlayerStatus() const
{
	string statusString = BuildPlayerStatusString();

	Common::PrintSystemMsg(statusString);

	Common::PauseAndClearScreen(3000);
}


string Player::BuildPlayerStatusString() const
{
	string strPlayerStatus = GetName() + " 용사의 스테이터스\n";

	strPlayerStatus += BuildBasicInfoString();

	strPlayerStatus += BuildStatsString();

	strPlayerStatus += BuildEquipInfoString();

	strPlayerStatus += BuildInventoryString();

	return strPlayerStatus;

}


string Player::BuildInventoryString() const
{
	string result = "\n인벤토리 아이템 목록 : ";

	const list<Item*>& inventoryItems = m_inventoryManager.GetAllItems();
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
	}	return result;
}

string Player::BuildEquipInfoString() const
{
	string strWeaponName, strArmorName;
	Weapon* equippedWeapon = m_EquipmentManager.GetWeapon();
	Armor* equippedArmor = m_EquipmentManager.GetArmor();

	if (equippedWeapon)
	{
		strWeaponName = equippedWeapon->GetItemName();
	}
	else
	{
		strWeaponName = "비어있음";
	}
	
	if (equippedArmor)
	{
		strArmorName = equippedArmor->GetItemName();
	}
	else
	{
		strArmorName = "비어있음";
	}

	return "장착 중인 무기 : " + strWeaponName + "\n"
		+ "장착 중인 방어구 : " + strArmorName + "\n"
		+ "보유 금화 : " + to_string(fPlayerInfo.playerGold) + "\n";
}

string Player::BuildStatsString() const
{
	return "공격력 : " + to_string(fPlayerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fPlayerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fPlayerInfo.characterStats.GetAgility()) + "\n\n";
}

string Player::BuildBasicInfoString() const
{
	return "현재 레벨 : " + to_string(fPlayerInfo.iCurrentLevel) + "\n"
		+ "경험치 : " + to_string(fPlayerInfo.playerExperience) + "/" + to_string(fPlayerInfo.playerMaxExperience) + "\n"
		+ "체력 : " + to_string(fPlayerInfo.iCurrentHealth) + "/" + to_string(fPlayerInfo.iMaxHealth) + "\n\n";
}