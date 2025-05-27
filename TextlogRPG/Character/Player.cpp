#include "Player.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

BaseCharacter& Player::CreateCharacter(const string& characterName)
{
   //TODO : Player SetCharacter Function 
	Player* player = new Player(characterName);

	return *player;
}

void Player::TakeDamage(int32_t damage)
{
	//TODO : Player TakeDamage Function 
	FCharacterInfo info = GetCharacterInfo();
	info.characterHealth = max(0, info.characterHealth - damage);
	SetCharacterInfo(info);

	if(info.characterHealth <= 0)
	{
		cout << "[System] 플레이어가 쓰러졌습니다!" << endl;
		return; 
	}
	else
	{
		cout << "[System] " << damage << " 만큼 데미지를 입음. 현재 체력: " << info.characterHealth << endl;
	}
}

void Player::Attack(BaseCharacter* target)
{
	//TODO : Player Attack Function
	int16_t damage = GetCharacterStats().attack - target->GetCharacterStats().defense;
	if (damage < 0)
	{
		damage = 0; 
	}
	cout << "[System] " << GetCharacterInfo().charracterName << " 가 " 
		<< target->GetCharacterInfo().charracterName << "을 공격하여 " << damage << "의 피해를 줌." << endl;
	target->TakeDamage(damage);
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
	//TODO : Player Destructor Function for Inventory
	//TODO : Player Destructor Function for MiscItem
	/*if (MiscItem != nullptr)
	{
		delete MiscItem;
		MiscItem = nullptr;
	}*/
	delete this; // Clean up the player instance
}
