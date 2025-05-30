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
	//TODO : 몬스터의 드랍아이템 pool_ csv에서 불러오기 구현
	Weapon* basicSword = new Weapon();
	basicSword->SetItem(EItemType::WEAPON, 50, 10, 0, 0, "초보자의 검");
	Weapon* ironSword = new Weapon();
	ironSword->SetItem(EItemType::WEAPON, 80, 15, 0, 0, "철검");
	Armor* basicArmor = new Armor();
	basicArmor->SetItem(EItemType::ARMOR, 60, 0, 10, 0, "초보자의 갑옷");
	Armor* leatherArmor = new Armor();
	leatherArmor->SetItem(EItemType::ARMOR, 100, 0, 15, 2, "가죽갑옷");
	MiscItem* brokenCoin = new MiscItem();
	brokenCoin->SetItem(EItemType::MISC, 25, 0, 0, 0, "조각난 금화");
	MiscItem* littleBread = new MiscItem();
	littleBread->SetItem(EItemType::MISC, 10, 0, 0, 0, "작은 빵");

	dropItems.push_back(basicSword);
	dropItems.push_back(ironSword);
	dropItems.push_back(basicArmor);
	dropItems.push_back(leatherArmor);
	dropItems.push_back(brokenCoin);
	dropItems.push_back(littleBread);
}




void Monster::TakeDamage(const BaseCharacter& target)
{
	int32_t damage = GetCharacterInfo().characterStats.GetDamage(target.GetCharacterInfo().characterStats);
	damage <= 0 ? damage = 0 : damage;
	FCharacterInfo& info = characterInfo;
	info.health -= damage;
	if (info.health <= 0)
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << info.characterName << "이(가) 쓰러졌습니다." << endl;
		cout << "[System] " << target.GetCharacterInfo().characterName << "은(는) 경험치와 아이템을 획득합니다." << endl;
		cout << "\n===========================================\n" << endl;
		info.health = 0; 
		Sleep(2000);
		system("cls");
		// 몬스터가 쓰러졌을 때 플레이어에게 경험치와 아이템 드랍
		const Player* playerTarget = dynamic_cast<const Player*>(&target);
		if (playerTarget)
		{
			// TODO : dropItems중에 랜덤	드랍
			Item* randomDropItem = dropItems[rand() % dropItems.size()];
			const_cast<Player*>(playerTarget)->GainLoot(dropExperience, dropGold, randomDropItem);
		};
		Sleep(2000);
		system("cls");
	}
	else
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] 당신은 "<< damage << "의 데미지를 입었습니다.\n현재 체력: " << info.health << endl;
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	
}

void Monster::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	target->TakeDamage(*this);
	/*if (target != nullptr)
	{
		target->Attack(this);
	}*/
}

Monster::~Monster()
{
	for (Item* item : dropItems)
	{
		delete item;
		item = nullptr;
	}
	dropItems.clear();
}
