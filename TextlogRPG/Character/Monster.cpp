#include "Monster.h"
#include "../Character/Player.h"
#include "../Item/ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

//Constructor
Monster::Monster(const FMonsterInfo& info)
	: BaseCharacter(info), fMonsterInfo(info), dropExperience(info.dropExperience), dropGold(info.dropGold)
{
	//setting the dropItemList of Monster
	dropItemList = ItemManager::GetInstance().GetItemList();
}


void Monster::TakeDamage(BaseCharacter& target)
{
	const FCharacterInfo& fTragetCharacterInfo = target.GetCharacterInfo();

	int32 iCalculatedDamage = fMonsterInfo.characterStats.CalculateDamage(fTragetCharacterInfo.characterStats);

	//무한루프 막기위해 최소데미지 1보장.
	if (iCalculatedDamage <= 0)
		iCalculatedDamage = 1;

	fMonsterInfo.iCurrentHealth -= iCalculatedDamage;
	if (fMonsterInfo.iCurrentHealth <= 0)
	{
		//print msg
		string strMonsterDefeatMesg = "몬스터 " + fMonsterInfo.strCharacterName + "이(가) 쓰러졌습니다.";
		Common::PrintSystemMsg(strMonsterDefeatMesg);

		fMonsterInfo.iCurrentHealth = 0;

		// 몬스터가 쓰러졌을 때 플레이어에게 경험치와 아이템 드랍
		Player* playerTarget = static_cast<Player*>(&target);
		if (playerTarget != nullptr && !dropItemList.empty())
		{
			// TODO : dropItems중에 랜덤드랍
			srand(static_cast<unsigned int>(time(NULL)));
			size_t randomIndex = rand() % dropItemList.size();

			string strRandomItemName = dropItemList[randomIndex];
			Item* randomDropItem = ItemManager::GetInstance().CreateItem(strRandomItemName);

			if (randomDropItem)
			{
				Common::PrintSystemMsg("전리품을 획득했습니다!");
				randomDropItem->ShowItemInfo();
				Common::PrintSystemMsg("이 아이템을 장착하시겠습니까?\n-> 1. 새로운 장비를 장착한다.  2. 기존의 장비를 사용한다.");
				
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
					Common::PrintSystemMsg("아이템을 인벤토리에 보관했습니다.");
				}
				else
				{
					Common::PrintSystemMsg("잘못된 입력입니다. 아이템을 획득하지 못했습니다.");
					return;
				}
			
				
				const_cast<Player*>(playerTarget)->GainLoot(dropExperience, dropGold, randomDropItem);
			}
			else 
			{
				Common::PrintSystemMsg("아이템 드랍을 실패했습니다.");
			}

		};
		Common::PauseAndClearScreen();
	}
	else
	{
		string strMonsterMsg = fMonsterInfo.strCharacterName + "은(는) " + to_string(iCalculatedDamage) + "의 데미지를 입었습니다.\n현재 체력: " + to_string(fMonsterInfo.iCurrentHealth);
		Common::PrintSystemMsg(strMonsterMsg);
		
	}
	
}

void Monster::Attack(BaseCharacter* target)
{
	if (target == nullptr) return;
	
	string strMonsterAttackMsg = fMonsterInfo.strCharacterName + "가(이) 당신을 공격합니다.\n";
	Common::PrintSystemMsg(strMonsterAttackMsg);

	target->TakeDamage(*this);
	
}

void Monster::SetCurrentHealth(int32 health)
{
	fMonsterInfo.iCurrentHealth = health;
}

Monster::~Monster()
{
	
}
