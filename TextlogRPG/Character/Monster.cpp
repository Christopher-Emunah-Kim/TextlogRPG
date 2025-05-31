#include "Monster.h"
#include "../Character/Player.h"
#include "../Item/ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

//Constructor
Monster::Monster(const string& name, int32_t health, int16_t attack, int16_t defense, int16_t agility, short level, int32_t exp, int32_t gold)
	: BaseCharacter(FCharacterInfo{ CharacterStatus{attack, defense, agility}, health, health, level, name }), dropExperience(exp), dropGold(gold) 
{
	dropItemList = ItemManager::GetInstance().GetItemList();
}




void Monster::TakeDamage(const BaseCharacter& target)
{
	int32_t damage = GetCharacterInfo().characterStats.GetDamage(target.GetCharacterInfo().characterStats);
	damage <= 0 ? damage = 0 : damage;
	FCharacterInfo& info = characterInfo;
	info.health -= damage;
	if (info.health <= 0)
	{
		system("cls");
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << info.characterName << "이(가) 쓰러졌습니다." << endl;
		//cout << "[System] 용사 " << target.GetCharacterInfo().characterName << "가(이) 경험치와 아이템을 획득합니다." << endl;
		cout << "\n===========================================\n" << endl;
		info.health = 0; 
		Sleep(2000);
		system("cls");
		// 몬스터가 쓰러졌을 때 플레이어에게 경험치와 아이템 드랍
		const Player* playerTarget = dynamic_cast<const Player*>(&target);
		if (playerTarget && !dropItemList.empty())
		{
			// TODO : dropItems중에 랜덤드랍
			srand(static_cast<unsigned int>(time(NULL)));
			size_t randomIndex = rand() % dropItemList.size();
			string randomItemName = dropItemList[randomIndex];
			Item* randomDropItem = ItemManager::GetInstance().GetItem(randomItemName);
			if (randomDropItem) {
				const_cast<Player*>(playerTarget)->GainLoot(dropExperience, dropGold, randomDropItem);
			}
			else {
				cout << "[System] 아이템 드랍에 실패했습니다." << endl;
			}

			/*Item* randomDropItem = dropItems[rand() % dropItems.size()];
			const_cast<Player*>(playerTarget)->GainLoot(dropExperience, dropGold, randomDropItem);*/
		};
		Sleep(2000);
		system("cls");
	}
	else
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] "<< info.characterName <<"은(는) "<< damage << "의 데미지를 입었습니다.\n현재 체력: " << info.health << endl;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	
}

void Monster::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	cout << "\n===========================================\n";
	cout << "\n[System] " << GetCharacterInfo().characterName << "가(이) 당신을 공격합니다.\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");

	target->TakeDamage(*this);
	
}

Monster::~Monster()
{
	
}
