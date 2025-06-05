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

	int32 iCalculatedDamage = playerInfo.characterStats.CalculateDamage(fTargetCharacterInfo.characterStats);
	
	playerInfo.iCurrentHealth -= iCalculatedDamage;

	if (playerInfo.iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
		playerInfo.iCurrentHealth = 0; // maintain gameover state with zero health
	}
	else
	{
		string strDamageText = target.GetCharacterInfo().strCharacterName + "에게 " + to_string(iCalculatedDamage) + "의 데미지를 입었습니다.\n당신의 현재 체력 : " + to_string(playerInfo.iCurrentHealth);
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
	playerInfo.strCharacterName = name;
}

string Player::GetName() const  
{  
    return playerInfo.strCharacterName;
}

FPlayerInfo Player::GetPlayerData() const
{
	return playerInfo;
}


void Player::AddToInventory(Item* item)
{
	if (item == nullptr)
		return;

	vector<Item*>::iterator it = find(inventory.begin(), inventory.end(), item);
	if (it == inventory.end()) {
		inventory.push_back(item);
	}
	else {
		Common::PrintSystemMsg("이미 보유 중인 아이템입니다.");
	}
}

vector<Item*> Player::GetInventoryItems(EItemType type) const
{
	vector<Item*> itemListByType;

	for (size_t i = 0; i < inventory.size(); ++i) 
	{
		Item* item = inventory[i];
		if (item->GetItemInfo().itemType == type)
		{
			itemListByType.push_back(item);
		}
	}
	return itemListByType;
}



void Player::EquipItem(Item* item)
{
	if (item == nullptr) 
		return;

	// add previous item to inventory 
	if(item->GetItemInfo().itemType== EItemType::WEAPON && playerInfo.weaponEquipped != nullptr) 
	{
		AddToInventory(playerInfo.weaponEquipped);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR && playerInfo.armorEquipped != nullptr)
	{
		AddToInventory(playerInfo.armorEquipped);
	}

	// remove status of former equipment(Weapon)
	CaculateNewStatus(item);

	UpdateFinalStatus(); // update status

	Common::PrintSystemMsg(item->GetItemInfo().itemName + "을(를) 장착합니다.");
	Common::PauseAndClearScreen(2000);

	ShowPlayerStatus();

}

void Player::CaculateNewStatus(Item* item)
{
	if (item->GetItemInfo().itemType == EItemType::WEAPON && playerInfo.weaponEquipped != nullptr) {
		equipmentStatus = CharacterStatus::NewStatus(
			equipmentStatus.GetAttack() - playerInfo.weaponEquipped->GetItemInfo().attack,
			equipmentStatus.GetDefense() - playerInfo.weaponEquipped->GetItemInfo().defense,
			equipmentStatus.GetAgility() - playerInfo.weaponEquipped->GetItemInfo().agility
		);
	}
	// remove status of former equipment(Armor)
	if (item->GetItemInfo().itemType == EItemType::ARMOR && playerInfo.armorEquipped != nullptr) {
		equipmentStatus = CharacterStatus::NewStatus(
			equipmentStatus.GetAttack() - playerInfo.armorEquipped->GetItemInfo().attack,
			equipmentStatus.GetDefense() - playerInfo.armorEquipped->GetItemInfo().defense,
			equipmentStatus.GetAgility() - playerInfo.armorEquipped->GetItemInfo().agility
		);
	}

	// update new equipment
	if (item->GetItemInfo().itemType == EItemType::WEAPON) {
		playerInfo.weaponEquipped = static_cast<Weapon*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR) {
		playerInfo.armorEquipped = static_cast<Armor*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::MISC)
	{
		playerInfo.miscOwned = static_cast<MiscItem*>(item);
	}

	// update status of new equipment
	equipmentStatus = CharacterStatus::NewStatus(
		equipmentStatus.GetAttack() + item->GetItemInfo().attack,
		equipmentStatus.GetDefense() + item->GetItemInfo().defense,
		equipmentStatus.GetAgility() + item->GetItemInfo().agility
	);
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) 
		return;
	
	vector<Item*>::iterator it = find(inventory.begin(), inventory.end(), item);
	if (it != inventory.end())
	{
		inventory.erase(it);
	}
	switch (item->GetItemInfo().itemType)
	{
	case EItemType::WEAPON:
	{
		if (playerInfo.weaponEquipped == item)
		{
			playerInfo.weaponEquipped = nullptr;
		}
	}
	break;
	case EItemType::ARMOR:
	{
		if (playerInfo.armorEquipped == item)
		{
			playerInfo.armorEquipped = nullptr;
		}
	}
	break;
	case EItemType::MISC:
	{
		if (playerInfo.miscOwned == item)
		{
			playerInfo.miscOwned = nullptr;
		}
	}
	break;
	}

}

void Player::Heal(int32 healAmount)
{
	if (healAmount <= 0) return;
	playerInfo.iCurrentHealth += healAmount;
	if (playerInfo.iCurrentHealth > playerInfo.iMaxHealth)
	{
		playerInfo.iCurrentHealth = playerInfo.iMaxHealth;
	}
}

void Player::UseGold(int32 cost)
{
	if (cost <= 0) return;
	if (playerInfo.playerGold >= cost)
	{
		playerInfo.playerGold -= cost;
		if (playerInfo.playerGold < 0)
		{
			playerInfo.playerGold = 0; 
		}
	}
}

void Player::EarnGold(int32 earnGold)
{
	if (earnGold <= 0) return;

	playerInfo.playerGold += earnGold;
	string strEarnGoldMsg = to_string(earnGold) + " 골드를 획득했습니다. 현재 골드: " + to_string(playerInfo.playerGold);
	Common::PrintSystemMsg(strEarnGoldMsg);
}

void Player::GainLoot(int32 experience, int32 gold, Item* item)
{
	if (experience < 0 || gold < 0) return;

	playerInfo.playerExperience += experience;
	playerInfo.playerGold += gold;

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

	if (playerInfo.playerExperience >= playerInfo.playerMaxExperience)
	{
		CharacterLevelUp();
	}
}

void Player::UpdateFinalStatus()
{
	playerInfo.characterStats = CharacterStatus::NewStatus(
		baseStatus.GetAttack() + equipmentStatus.GetAttack(),
		baseStatus.GetDefense() + equipmentStatus.GetDefense(),
		baseStatus.GetAgility() + equipmentStatus.GetAgility()
	);
}

BaseCharacter& Player::CharacterLevelUp()
{
	//Update Player's level and status based on LevelData Array
	playerInfo.iCurrentLevel++;
	if (playerInfo.iCurrentLevel > 100)
	{
		playerInfo.iCurrentLevel = 100; // MAX LEVEL
		return *this;
	}

	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(characterInfo.iCurrentLevel);

	playerInfo.iMaxHealth += levelData.maxHealthPerLevel;
	playerInfo.playerMaxExperience += levelData.maxExperiencePerLevel;
	playerInfo.iCurrentHealth = playerInfo.iMaxHealth; // Reset current health to max health after level up

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
	playerInfo.characterStats = CharacterStatus::NewStatus(playerAtk, playerDef, playerAgi);

	UpdateFinalStatus();

	string strLevelUpMsg = "레벨업!\n현재 레벨 : " + to_string(playerInfo.iCurrentLevel) + "\n"
		+ "체력 : " + to_string(playerInfo.iCurrentHealth) + "/" + to_string(playerInfo.iMaxHealth) + "\n"
		+ "공격력 : " + to_string(playerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(playerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(playerInfo.characterStats.GetAgility());

	Common::PrintSystemMsg(strLevelUpMsg);
	return *this; 
}

void Player::ShowPlayerStatus()
{
	string strWeaponName, strArmorName, strMiscItemName;
	if (playerInfo.weaponEquipped != nullptr)
	{
		strWeaponName = playerInfo.weaponEquipped->GetItemName();
	}
	else
	{
		strWeaponName = "비어있음";
	}
	
	if (playerInfo.armorEquipped != nullptr)
	{
		strArmorName = playerInfo.armorEquipped->GetItemName();
	}
	else
	{
		strArmorName = "비어있음";
	}

	if (playerInfo.miscOwned != nullptr)
	{
		strMiscItemName = playerInfo.miscOwned->GetItemName();
	}
	else
	{
		strMiscItemName = "비어있음";
	}
	

	string strPlayerStatus = GetName() + " 용사의 스테이터스\n"
		+ "현재 레벨 : " + to_string(playerInfo.iCurrentLevel) + "\n"
		+ "경험치 : " + to_string(playerInfo.playerExperience) + "/" + to_string(playerInfo.playerMaxExperience) + "\n"
		+ "체력 : " + to_string(playerInfo.iCurrentHealth) + "/" + to_string(playerInfo.iMaxHealth) + "\n\n"
		+ "공격력 : " + to_string(playerInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(playerInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(playerInfo.characterStats.GetAgility()) + "\n\n"
		+ "장착 중인 무기 : " + strWeaponName + "\n"
		+ "장착 중인 방어구 : " + strArmorName + "\n"
		+ "보유 중인 아이템 : " + strMiscItemName + "\n\n"
		+ "보유 금화 : " + to_string(playerInfo.playerGold) + "\n";

	Common::PrintSystemMsg(strPlayerStatus);

	Common::PauseAndClearScreen(3500);
}


Player::~Player()
{
	if (playerInfo.weaponEquipped != nullptr)
	{
		delete playerInfo.weaponEquipped;
		playerInfo.weaponEquipped = nullptr;
	}
	if (playerInfo.armorEquipped != nullptr)
	{
		delete playerInfo.armorEquipped;
		playerInfo.armorEquipped = nullptr;
	}
	if (playerInfo.miscOwned != nullptr)
	{
		delete playerInfo.miscOwned;
		playerInfo.miscOwned = nullptr;
	}
	for (size_t i = 0; i<inventory.size(); ++i)
	{
		Item* item = inventory[i];
		delete item;
	}
	inventory.clear();
	
}
