#include "Player.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

Player* Player::CreateCharacter(const string& characterName)
{
	//TODO : 임시_이후 LevelData 연결
	FCharacterInfo characterInfo = { CharacterStatus::NewStatus(10, 5, 3),100, 100, 1, characterName };
 
	FPlayerData playerData;

	Player* player = new Player(playerData, characterInfo);

	return player;
}

void Player::TakeDamage(const BaseCharacter& target)
{
	int32_t damage = GetCharacterInfo().characterStats.GetDamage(target.GetCharacterInfo().characterStats);

	FCharacterInfo info = GetCharacterInfo();

	//데미지 적용


	if (info.health <= 0)
	{
		cout << "[System] 플레이어가 쓰러졌습니다!" << endl;
		return;
	}
	else
	{
		cout << "[System] " << damage << " 만큼 데미지를 입음. 현재 체력: " << info.health << endl;
	}
}

void Player::Attack(BaseCharacter* target)
{
	//TODO : Player Attack Function
	
}

void Player::SetName(const string& name)
{

}

string Player::GetName() const  
{  
    return GetCharacterInfo().characterName;  
}

FPlayerData Player::GetPlayerData() const
{
	return playerData;
}


void Player::EquipItem(Item* item)
{
}

void Player::LoseItem(Item* item)
{
}

void Player::Heal(int32_t amount)
{
}

void Player::UseGold(int32_t amount)
{

}

void Player::EarnGold(int32_t amount)
{
}

void Player::GainLoot(int32_t experience, int32_t gold, Item* item)
{
}

//BaseCharacter& Player::CharacterLevelUp()
//{
//	// TODO: 여기에 return 문을 삽입합니다.
//}

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
	//TODO : Player Destructor Function for Inventory
	//TODO : Player Destructor Function for MiscItem
	/*if (MiscItem != nullptr)
	{
		delete MiscItem;
		MiscItem = nullptr;
	}*/
}
