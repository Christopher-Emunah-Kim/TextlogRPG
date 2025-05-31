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
	FCharacterInfo characterInfo = { CharacterStatus::NewStatus(10, 5, 3),5, 5, 1, characterName };
 
	FPlayerData playerData;

	Player* player = new Player(playerData, characterInfo);

	return player;
}

void Player::TakeDamage(const BaseCharacter& target)
{
	//플레이어의 TakeDamage함수 내에서 몬스터와 플레이어의 데미지 계산 및 출력메시지 대부분 처리
	//몬스터의 TekeDamage함수는 최소한으로 유지
	int32_t damage = GetCharacterInfo().characterStats.GetDamage(target.GetCharacterInfo().characterStats);
	damage > 0? damage : 1; //무한루프 막기위해 최소데미지 1보장.
	FCharacterInfo& info = characterInfo;
	info.health -= damage;
	if (info.health <= 0)
	{
		cout << "\n===========================================\n";
		cout << "[System] 당신은 여신의 곁으로 돌아갑니다.... ";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		//TODO : 게임오버로직 추가
		//gameMode.SetGameState(EGameState::GAME_OVER);
		info.health = 0; // 체력을 0으로 설정하여 게임오버 상태로 유지
	}
	else
	{
		cout << "\n===========================================\n";
		cout << "[System] " << target.GetCharacterInfo().characterName << "에게" 
				<< damage << "의 데미지를 입었습니다. 현재 체력: " << info.health;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
}

void Player::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	cout << "\n===========================================\n";
	cout << "\n[System] " << target->GetCharacterInfo().characterName <<"을(를) 공격합니다.\n";
	cout << "\n===========================================\n" << endl;

	target->TakeDamage(*this);
	
}

void Player::SetName(const string& name)
{
	characterInfo.characterName = name;
}

string Player::GetName() const  
{  
    return characterInfo.characterName;
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

	for (Item* item : inventory) 
	{
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

	// remove status of former equipment(Weapon)
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
		playerData.weaponEquipped = dynamic_cast<Weapon*>(item);
	}
	if (item->GetItemInfo().itemType == EItemType::ARMOR) {
		playerData.armorEquipped = dynamic_cast<Armor*>(item);
	}

	// update status of new equipment
	equipmentStatus = CharacterStatus::NewStatus(
		equipmentStatus.GetAttack() + item->GetItemInfo().attack,
		equipmentStatus.GetDefense() + item->GetItemInfo().defense,
		equipmentStatus.GetAgility() + item->GetItemInfo().agility
	);

	UpdateFinalStatus(); // update status

	// update and display the result of the equipment change
	item->Use(this);



	/*switch (item->GetItemInfo().itemType)
	{
		case EItemType::WEAPON:
		{
			if (playerData.weaponEquipped != nullptr)
			{
				LoseItem(playerData.weaponEquipped);
			}
			playerData.weaponEquipped = dynamic_cast<Weapon*>(item);

			item->Use(this);
		}
			break;
		case EItemType::ARMOR:
		{
			if (playerData.armorEquipped != nullptr)
			{
				LoseItem(playerData.armorEquipped);
			}
			playerData.armorEquipped = dynamic_cast<Armor*>(item);

			item->Use(this);

		}
			break;
		case EItemType::MISC:
		{
			if (playerData.miscOwned != nullptr)
			{
				LoseItem(playerData.miscOwned);
			}
			playerData.miscOwned = dynamic_cast<MiscItem*>(item);
			cout << "\n===========================================\n";
			cout << "[System] " << item->GetItemInfo().itemName << "을(를) 얻었습니다.";
			cout << "\n===========================================\n" << endl;
		}
			break;
	}*/
}

void Player::LoseItem(Item* item)
{
	if (item == nullptr) return;
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

void Player::Heal(int32_t healAmount)
{
	if (healAmount <= 0) return;
	characterInfo.health += healAmount;
	if (characterInfo.health > characterInfo.maxHealth)
	{
		characterInfo.health = characterInfo.maxHealth;
	}
}

void Player::UseGold(int32_t cost)
{
	if (cost <= 0) return;
	if (playerData.playerGold >= cost)
	{
		playerData.playerGold -= cost;
		if (playerData.playerGold < 0)
		{
			playerData.playerGold = 0; 
		}
		/*cout << "\n===========================================\n";
		cout << "\n[System] "<< cost << "를 사용했습니다. 현재 골드: " << playerData.playerGold << "\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");*/
	}
	else
	{
		/*cout << "\n===========================================\n";
		cout << "\n[System] 골드가 부족합니다. 현재 골드: " << playerData.playerGold;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");*/
	}
}

void Player::EarnGold(int32_t earnGold)
{
	if (earnGold <= 0) return;

	playerData.playerGold += earnGold;
	cout << "\n===========================================\n";
	cout << "\n[System] " << earnGold << " 골드를 획득했습니다. 현재 골드: " << playerData.playerGold;
	cout << "\n===========================================\n" << endl;
}

void Player::GainLoot(int32_t experience, int32_t gold, Item* item)
{
	if (experience < 0 || gold < 0) return;

	playerData.playerExperience += experience;
	playerData.playerGold += gold;
	cout << "\n===========================================\n";
	cout << "\n[System] 최종 전투 결과입니다!!\n";
	cout << "\n[System] " << experience << " 경험치와 " << gold << " 골드를 획득했습니다.\n";
	if (item != nullptr)
	{
		AddToInventory(item);
		cout << "\n[System] 아이템 " << item->GetItemInfo().itemName << "을(를) 획득했습니다.\n";
	}
	cout << "\n===========================================\n" << endl;

	Sleep(2000);
	system("cls");

	ShowPlayerStatus(this);

	//TODO : 레벨업 로직 구현
	if (playerData.playerExperience >= playerData.playerMaxExperience)
	{
		CharacterLevelUp();
	}
}

void Player::UpdateFinalStatus()
{
	characterInfo.characterStats = CharacterStatus::NewStatus(
		baseStatus.GetAttack() + equipmentStatus.GetAttack(),
		baseStatus.GetDefense() + equipmentStatus.GetDefense(),
		baseStatus.GetAgility() + equipmentStatus.GetAgility()
	);
}

BaseCharacter& Player::CharacterLevelUp()
{
	//TODO : 레벨업할때 장비스탯 제대로 반영안되는것같은데 해결 필요.

	//LevelData 클래스의 FLevelData 구조체 어레이를 사용하여 레벨업 시 캐릭터의 상태를 업데이트
	FCharacterInfo& info = characterInfo;
	info.level++;
	LevelData levelDataInstance;
	FLevelProperties levelData = levelDataInstance.GetLevelData(info.level);
	info.maxHealth += levelData.maxHealthPerLevel;
	info.health = info.maxHealth; // 레벨업 시 체력을 최대치로 회복

	// 레벨업 시 공격력, 방어력, 민첩성 증가
	// CharacterStatus의 NewStatus 객체 반환 메서드를 사용하여 상태 업데이트
	info.characterStats = CharacterStatus::NewStatus(
		levelData.attackPerLevel,
		levelData.defensePerLevel,
		levelData.agilityPerLevel
	);

	UpdateFinalStatus()

	cout << "\n===========================================\n";
	cout << "\n[System] 레벨업!\n";
	cout << "현재 레벨 : " << info.level;
	cout << "\n체력: " << info.health << "/" << info.maxHealth;
	cout << "\n공격력: " << info.characterStats.GetAttack();
	cout << "\n방어력: " << info.characterStats.GetDefense();
	cout << "\n민첩성: " << info.characterStats.GetAgility();
	cout << "\n===========================================\n" << endl;

	Sleep(4000);
	system("cls");
	return *this; 
}

void Player::ShowPlayerStatus(Player* player)
{
	//플레이어 현재 상태 보여주는 함수
	FCharacterInfo& info = player->characterInfo;
	cout << "\n===========================================\n";
	cout << "\n[System] "<< player->GetName() << "용사의 스탯창!\n";
	cout << "\n현재 레벨 : " << info.level << "\n";
	cout << "\n체력: " << info.health << "/" << info.maxHealth << "\n";
	cout << "\n공격력: " << info.characterStats.GetAttack() << "\n";
	cout << "\n방어력: " << info.characterStats.GetDefense() << "\n";
	cout << "\n민첩성: " << info.characterStats.GetAgility() << "\n";
	cout << "\n\n===========================================\n" << endl;

	Sleep(4000);
	system("cls");
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
	for (Item* item : inventory)
	{
		delete item;
	}
	inventory.clear();
	
}
