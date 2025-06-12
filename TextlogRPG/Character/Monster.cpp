#include "Monster.h"
#include "../Character/Player.h"
#include "../Core/ItemManager.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/MiscItem.h"

//Constructor
Monster::Monster(const FMonsterInfo& info)
	: fMonsterInfo(info), dropExperience(info.dropExperience), dropGold(info.dropGold)
{
	Initialize(info);
}

void Monster::Initialize(const FMonsterInfo& info)
{
	//setting the dropItemList of Monster
	dropItemNames = ItemManager::GetInstance().GetItemList();
	isDefeated = false;
	lastCalculatedDamage = 0;
	lastDropItem = nullptr;
}

void Monster::ApplyDamageFrom(BaseCharacter& attacker)
{
	UpdateDamage(attacker);

	RenderDamageResult();

	if (isDefeated)
	{
		Player* playerAttacker = dynamic_cast<Player*>(&attacker);
		if (playerAttacker != nullptr && !dropItemNames.empty()) 
		{
			bool dropSuccess = ProcessItemDrop(playerAttacker);
			RenderItemDropResult(lastDropItem, dropSuccess, playerAttacker);
		}
		Common::PauseAndClearScreen(2000);
	}
	
}

void Monster::UpdateDamage(BaseCharacter& attacker)
{
	const FCharacterInfo& fAttackerCharacterInfo = attacker.GetCharacterInfo();

	lastCalculatedDamage = fMonsterInfo.characterStats.CalculateDamage(fAttackerCharacterInfo.characterStats);

	fMonsterInfo.iCurrentHealth -= lastCalculatedDamage;
	if (fMonsterInfo.iCurrentHealth <= 0)
	{
		fMonsterInfo.iCurrentHealth = 0;
		isDefeated = true;
	}
}


void Monster::RenderDamageResult()
{
	if (isDefeated)
	{
		string strMonsterDefeatMsg = fMonsterInfo.strCharacterName + "은(는) " + to_string(lastCalculatedDamage) + "의 데미지를 입었습니다.";
		Common::PrintSystemMsg(strMonsterDefeatMsg);

		string strMonsterDefeatMesg = "몬스터 " + fMonsterInfo.strCharacterName + "이(가) 쓰러졌습니다.";
		Common::PrintSystemMsg(strMonsterDefeatMesg);
	}
	else
	{
		string strMonsterMsg = fMonsterInfo.strCharacterName + "은(는) " + to_string(lastCalculatedDamage) + "의 데미지를 입었습니다.\n현재 체력: " + to_string(fMonsterInfo.iCurrentHealth);
		Common::PrintSystemMsg(strMonsterMsg);
	}
}

bool Monster::ProcessItemDrop(Player* playerTarget)
{
	if (dropItemNames.empty()) 
	{
		return false; 
	}

	srand(static_cast<unsigned int>(time(NULL)));
	size_t randomIndex = rand() % dropItemNames.size();

	string strRandomItemName = dropItemNames[randomIndex];

	lastDropItem = ItemManager::GetInstance().CreateItem(strRandomItemName);

	return (lastDropItem != nullptr);
}


void Monster::RenderItemDropResult(Item* droppedItem, bool isSuccessful, Player* attacker)
{
	if (!isSuccessful || droppedItem == nullptr)
	{
		Common::PrintSystemMsg("아이템 드랍을 실패했습니다.");
		return;
	}

	Common::PrintSystemMsg("전리품을 획득했습니다!");
	droppedItem->ShowItemInfo();


	Common::PrintSystemMsg("이 아이템을 등록하시겠습니까?\n-> 1. 새로운 아이템을 등록한다.  2. 기존의 아이템을 사용한다.");
	char equipChoice = Common::GetCharInput();

	Player* playerTarget = dynamic_cast<Player*>(attacker);

	if (playerTarget == nullptr) 
		return;

	if (equipChoice == '1')
	{
		playerTarget->EquipItem(droppedItem);
	}
	else if (equipChoice == '2')
	{
		playerTarget->AddToInventory(droppedItem);
		Common::PrintSystemMsg("아이템을 인벤토리에 보관했습니다.");
	}
	else
	{
		Common::PrintSystemMsg("잘못된 입력입니다. 아이템을 획득하지 못했습니다.");
		return;
	}

	playerTarget->GainLoot(dropExperience, dropGold, droppedItem);
}



void Monster::Attack(BaseCharacter* target)
{
	if (target == nullptr) 
		return;
	
	RenderAttackMessage();

	UpdateAttack(target);
	
}

void Monster::UpdateAttack(BaseCharacter* target)
{
	if (target != nullptr)
	{
		target->ApplyDamageFrom(*this);
	}
}


void Monster::RenderAttackMessage()
{
	string strMonsterAttackMsg = fMonsterInfo.strCharacterName + "이(가) 당신을 공격합니다.";
	Common::PrintSystemMsg(strMonsterAttackMsg);

	Common::PauseAndClearScreen(3000);
}



void Monster::SetCurrentHealth(int32 health)
{
	fMonsterInfo.iCurrentHealth = health;
	isDefeated = (health <= 0);
}

void Monster::RenderMonsterStatus() const
{
	string strMonsterStatus = " [몬스터 도감] " + fMonsterInfo.strCharacterName + " (상세보기)\n"
		+ "몬스터 레벨 : " + to_string(fMonsterInfo.iCurrentLevel) + "\n"
		+ "체력 : " + to_string(fMonsterInfo.iCurrentHealth) + "/" + to_string(fMonsterInfo.iMaxHealth) + "\n\n"
		+ "공격력 : " + to_string(fMonsterInfo.characterStats.GetAttack()) + "\n"
		+ "방어력 : " + to_string(fMonsterInfo.characterStats.GetDefense()) + "\n"
		+ "민첩성 : " + to_string(fMonsterInfo.characterStats.GetAgility());

	Common::ShowOption(strMonsterStatus);

	cout << "Enter 키를 눌러 계속 진행하세요.\n" << endl;
	//cin.ignore(1024, '\n');
	InputManager::GetInstance().GetLineInput();
}


Monster::~Monster()
{
	
}
