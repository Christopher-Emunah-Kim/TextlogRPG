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
	FCharacterInfo fTempCharacterInfo = { CharacterStatus::NewStatus(10, 5, 3), 5, 5, 1, characterName };

	FPlayerData playerData;

	Player* player = new Player(playerData, fTempCharacterInfo);

	return player;
}

void Player::TakeDamage(BaseCharacter& target)
{
	//플레이어의 TakeDamage함수 내에서 몬스터와 플레이어의 데미지 계산 및 출력메시지 대부분 처리
	const FCharacterInfo& fTargetCharacterInfo = target.GetCharacterInfo();

	int32 iCalculatedDamage = playerData.characterStats.CalculateDamage(fTargetCharacterInfo.characterStats);

	//무한루프 막기위해 최소데미지 1보장.
	if (iCalculatedDamage <= 0)
		iCalculatedDamage = 1;
	
	playerData.iCurrentHealth -= iCalculatedDamage;

	if (playerData.iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
		playerData.iCurrentHealth = 0; // 체력을 0으로 설정하여 게임오버 상태로 유지
	}
	else
	{
		string strDamageText = "[System] " + target.GetCharacterInfo().strCharacterName + "에게 " + to_string(iCalculatedDamage) + "의 데미지를 입었습니다.";
		Common::PrintSystemMsg(strDamageText);
	}
	Common::PauseAndClearScreen();
}

void Player::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	string strAttackText = "[System] 당신은 " + target->GetCharacterInfo().strCharacterName + "을(를) 공격합니다.";
	Common::PrintSystemMsg(strAttackText);
	Common::PauseAndClearScreen();

	target->TakeDamage(*this);
	
}

void Player::SetName(const string& name)
{
	playerData.strCharacterName = name;
}

string Player::GetName() const  
{  
    return playerData.strCharacterName;
}

FPlayerData Player::GetPlayerData() const
{
	return playerData;
}


void Player::AddToInventory(Item* item)
{
	inventory.push_back(item);
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
	if (item == nullptr) return;
	//TODO : 아이템 착용 후 캐릭터 스탯 이상하게 덮어씌워지는 문제 확인
	// remove status of former equipment(Weapon)
	CaculateNewStatus(item);

	UpdateFinalStatus(); // update status

	// update the equipment change
	//item->EquippedBy(this);

	string strUseWeapon = item->GetItemInfo().itemName + "을(를) 장착합니다.\n";
	Common::PrintSystemMsg(strUseWeapon);
	Common::PauseAndClearScreen();

	ShowPlayerStatus();

}

void Player::CaculateNewStatus(Item* item)
{
	if (item->GetItemInfo().itemType == EItemType::WEAPON && playerData.weaponEquipped != nullptr) {
		equipmentStatus = CharacterStatus::NewStatus(
			equipmentStatus.GetAttack() - playerData.weaponEquipped->GetItemInfo().attack,
			equipmentStatus.GetDefense() - playerData.weaponEquipped->GetItemInfo().defense,
			equipmentStatus.GetAgility() - playerData.weaponEquipped->GetItemInfo().agility
		);
	}
	// remove status of former equipment(Armor)
	if (item->GetItemInfo().itemType == EItemType::ARMOR && playerData.armorEquipped != nullptr) {
		equipmentStatus = CharacterStatus::NewStatus(
			equipmentStatus.GetAttack() - playerData.armorEquipped->GetItemInfo().attack,
			equipmentStatus.GetDefense() - playerData.armorEquipped->GetItemInfo().defense,
			equipmentStatus.GetAgility() - playerData.armorEquipped->GetItemInfo().agility
		);
	}

	// update new equipment
	if (item->GetItemInfo().itemType == EItemType::WEAPON) {
		playerData.weaponEquipped = static_cast<Weapon*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR) {
		playerData.armorEquipped = static_cast<Armor*>(item);
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
		if (playerData.weaponEquipped == item)
		{
			playerData.weaponEquipped = nullptr;
		}
	}
	break;
	case EItemType::ARMOR:
	{
		if (playerData.armorEquipped == item)
		{
			playerData.armorEquipped = nullptr;
		}
	}
	break;
	case EItemType::MISC:
	{
		if (playerData.miscOwned == item)
		{
			playerData.miscOwned = nullptr;
		}
	}
	break;
	}

}

void Player::Heal(int32 healAmount)
{
	if (healAmount <= 0) return;
	playerData.iCurrentHealth += healAmount;
	if (playerData.iCurrentHealth > playerData.iMaxHealth)
	{
		playerData.iCurrentHealth = playerData.iMaxHealth;
	}
}

void Player::UseGold(int32 cost)
{
	if (cost <= 0) return;
	if (playerData.playerGold >= cost)
	{
		playerData.playerGold -= cost;
		if (playerData.playerGold < 0)
		{
			playerData.playerGold = 0; 
		}
	}
}

void Player::EarnGold(int32 earnGold)
{
	if (earnGold <= 0) return;

	playerData.playerGold += earnGold;
	string strEarnGoldMsg = "[System] " + to_string(earnGold) + " 골드를 획득했습니다. 현재 골드: " + to_string(playerData.playerGold);
	Common::PrintSystemMsg(strEarnGoldMsg);
}

void Player::GainLoot(int32 experience, int32 gold, Item* item)
{
	if (experience < 0 || gold < 0) return;

	playerData.playerExperience += experience;
	playerData.playerGold += gold;

	Common::PrintLine();
	cout << "\n[System] 최종 전투 결과입니다!!\n";
	cout << "\n[System] " << experience << " 경험치와 " << gold << " 골드를 획득했습니다.\n";
	if (item != nullptr)
	{
		AddToInventory(item);
		cout << "\n[System] 아이템 " << item->GetItemInfo().itemName << "을(를) 획득했습니다.\n";
	}
	Common::PrintLine();

	ShowPlayerStatus();

	//TODO : 레벨업 로직 구현
	if (playerData.playerExperience >= playerData.playerMaxExperience)
	{
		CharacterLevelUp();
	}
}

void Player::UpdateFinalStatus()
{
	playerData.characterStats = CharacterStatus::NewStatus(
		baseStatus.GetAttack() + equipmentStatus.GetAttack(),
		baseStatus.GetDefense() + equipmentStatus.GetDefense(),
		baseStatus.GetAgility() + equipmentStatus.GetAgility()
	);
}

BaseCharacter& Player::CharacterLevelUp()
{
	//TODO : 레벨업할때 장비스탯 제대로 반영안되는것같은데 해결 필요.
	//LevelData 클래스의 FLevelData 구조체 어레이를 사용하여 레벨업 시 캐릭터의 상태를 업데이트
	playerData.iCurrentLevel++;
	if (playerData.iCurrentLevel > 100)
	{
		playerData.iCurrentLevel = 100; // 최대 100 레벨 초과 방지
		return *this;
	}

	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(characterInfo.iCurrentLevel);

	playerData.iMaxHealth += levelData.maxHealthPerLevel;
	playerData.iCurrentHealth = characterInfo.iMaxHealth; // 레벨업 시 체력을 최대치로 회복

	// 레벨업 시 공격력, 방어력, 민첩성 증가
	playerData.characterStats = CharacterStatus::NewStatus(levelData.attackPerLevel, levelData.defensePerLevel,levelData.agilityPerLevel	);

	UpdateFinalStatus();

	string strLevelUpMsg = "레벨업!\n현재 레벨 : " + to_string(playerData.iCurrentLevel)
		+ "체력 : " + to_string(playerData.iCurrentHealth) + "/" + to_string(playerData.iMaxHealth)
		+ "공격력 : " + to_string(playerData.characterStats.GetAttack())
		+ "방어력 : " + to_string(playerData.characterStats.GetDefense())
		+ "민첩성 : " + to_string(playerData.characterStats.GetAgility());

	Common::PrintSystemMsg(strLevelUpMsg);
	return *this; 
}

void Player::ShowPlayerStatus()
{
	string strWeaponName, strArmorName, strMiscItemName;
	if (playerData.weaponEquipped != nullptr)
	{
		strWeaponName = playerData.weaponEquipped->GetItemName();
	}
	else
	{
		strWeaponName = "비어있음";
	}
	
	if (playerData.armorEquipped != nullptr)
	{
		strArmorName = playerData.armorEquipped->GetItemName();
	}
	else
	{
		strArmorName = "비어있음";
	}

	if (playerData.miscOwned != nullptr)
	{
		strMiscItemName = playerData.miscOwned->GetItemName();
	}
	else
	{
		strMiscItemName = "비어있음";
	}
	

	string strPlayerStatus = GetName() + " 용사의 스테이터스\n"
		+ "현재 레벨 : " + to_string(playerData.iCurrentLevel) + "\n"
		+ "경험치 : " + to_string(playerData.playerExperience) + "/" + to_string(playerData.playerMaxExperience) + "\n"
		+ "체력 : " + to_string(playerData.iCurrentHealth) + "/" + to_string(playerData.iMaxHealth) + "\n\n"
		+ "공격력 : " + to_string(playerData.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(playerData.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(playerData.characterStats.GetAgility()) + "\n\n"
		+ "장착 중인 무기 : " + strWeaponName + "\n"
		+ "장착 중인 방어구 : " + strArmorName + "\n"
		+ "보유 중인 아이템 : " + strMiscItemName + "\n\n"
		+ "보유 금화 : " + to_string(playerData.playerGold) + "\n";

	Common::PrintSystemMsg(strPlayerStatus);

	Common::PauseAndClearScreen(3000);
}


Player::~Player()
{
	if (playerData.weaponEquipped != nullptr)
	{
		delete playerData.weaponEquipped;
		playerData.weaponEquipped = nullptr;
	}
	if (playerData.armorEquipped != nullptr)
	{
		delete playerData.armorEquipped;
		playerData.armorEquipped = nullptr;
	}
	if (playerData.miscOwned != nullptr)
	{
		delete playerData.miscOwned;
		playerData.miscOwned = nullptr;
	}
	for (size_t i = 0; i<inventory.size(); ++i)
	{
		Item* item = inventory[i];
		delete item;
	}
	inventory.clear();
	
}
