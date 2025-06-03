#include "Monster.h"
#include "../Character/Player.h"
#include "../Item/ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

//Constructor
Monster::Monster(const FMonsterInfo& info)
	: BaseCharacter(info), dropExperience(info.dropExperience), dropGold(info.dropGold)
{
	dropItemList = ItemManager::GetInstance().GetItemList();
}




void Monster::TakeDamage(BaseCharacter& target)
{
	uint32 damage = GetCharacterInfo().characterStats.GetDamage(target.GetCharacterInfo().characterStats);
	damage <= 0 ? damage = 0 : damage;
	FCharacterInfo& info = characterInfo;
	info.iCurrentHealth -= damage;
	if (info.iCurrentHealth <= 0)
	{
		
		cout << "\n===========================================\n";
		cout << "\n[System] " << info.strCharacterName << "이(가) 쓰러졌습니다.\n";
		cout << "\n===========================================\n" << endl;
		info.iCurrentHealth = 0; 

		// 몬스터가 쓰러졌을 때 플레이어에게 경험치와 아이템 드랍
		Player* playerTarget = static_cast<Player*>(&target);
		if (playerTarget != nullptr && !dropItemList.empty())
		{
			// TODO : dropItems중에 랜덤드랍
			srand(static_cast<unsigned int>(time(NULL)));
			size_t randomIndex = rand() % dropItemList.size();
			string randomItemName = dropItemList[randomIndex];
			Item* randomDropItem = ItemManager::GetInstance().CreateItem(randomItemName);

			if (randomDropItem)
			{
				cout << "\n===========================================\n";
				cout << "\n[System] 전리품을 획득했습니다!!!\n";
				randomDropItem->ShowItemInfo();
				cout << "\n[System] 이 아이템을 장착하시겠습니까?\n";
				cout << "\n-> 1. 새로운 장비를 장착한다.  2. 기존의 장비를 사용한다.\n";
				cout << "\n===========================================\n" << endl;
				char equipChoice;
				cin >> equipChoice;
				cin.ignore(1024, '\n');

				if (equipChoice == '1')
				{
					playerTarget->EquipItem(randomDropItem);
					playerTarget->AddToInventory(randomDropItem);
				}
				else if (equipChoice == '2')
				{
					playerTarget->AddToInventory(randomDropItem);
					cout << "\n===========================================\n";
					cout << "\n[System] 아이템을 인벤토리에 보관했습니다\n";
					cout << "\n===========================================\n" << endl;
				}
				else
				{
					cout << "\n===========================================\n";
					cout << "[System] 잘못된 입력입니다. 아이템을 획득하지 못했습니다." << endl;
					cout << "\n===========================================\n" << endl;
					return;
				}
			
				
				const_cast<Player*>(playerTarget)->GainLoot(dropExperience, dropGold, randomDropItem);
			}
			else {
				cout << "[System] 아이템 드랍에 실패했습니다." << endl;
			}

		};
		Common::PauseAndClearScreen();
	}
	else
	{
		cout << "\n===========================================\n" << endl;
		cout << "[System] "<< info.strCharacterName <<"은(는) "<< damage << "의 데미지를 입었습니다.\n현재 체력: " << info.iCurrentHealth << endl;
		cout << "\n===========================================\n" << endl;
		
	}
	
}

void Monster::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	cout << "\n===========================================\n";
	cout << "\n[System] " << GetCharacterInfo().strCharacterName << "가(이) 당신을 공격합니다.\n";
	cout << "\n===========================================\n" << endl;
	

	target->TakeDamage(*this);
	
}

Monster::~Monster()
{
	
}
