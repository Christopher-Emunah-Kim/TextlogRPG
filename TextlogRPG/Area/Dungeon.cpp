#include "Dungeon.h"
#include "../Character/Player.h"
#include "../Character/Monster.h"
#include "../Util/Dialogue.h"

Dungeon::Dungeon()
{
	monsters.clear();
	stages.clear();
	currentStageIndex = 0;
}

Dungeon::Dungeon(vector<vector<FMonsterInfo>>& stageMonsterInfo)
{
	for (const vector<FMonsterInfo>& monsterInfos : stageMonsterInfo)
	{
		stages.emplace_back(new DungeonStage(monsterInfos));
	}
	currentStageIndex = 0;
}

DungeonStage* Dungeon::GetCurrentStage()
{
	if (currentStageIndex < stages.size())
	{
		return stages[currentStageIndex];
	}
	return nullptr;

}

bool Dungeon::NextStage()
{
	if (currentStageIndex + 1 < stages.size())
	{
		++currentStageIndex;
		return true;
	}
	return false;
}

void Dungeon::Enter(Player* player)
{
	Common::PrintSystemMsg("던전 탐험을 시작합니다.");
	Common::PrintSystemMsg("기억하십시오. 심연을 들여다볼수록,\n 당신 또한 심연에 물들 것입니다.");
	Common::PauseAndClearScreen();

	Dialogue::ShowOption("[System] 던전의 입구에 도착했습니다. 도전하시겠습니까?\n\n1. 인생은 모험이지!\n2. 아니 지금은 아닌것 같아.(마을로 돌아간다)");
}

void Dungeon::AddMonster(Monster* monster) {
	monsters.push_back(monster);
}

void Dungeon::RemoveMonster(Monster* monster) {
	monsters.erase(remove(monsters.begin(), monsters.end(), monster), monsters.end());
}

vector<Monster*>& Dungeon::GetMonsterList() 
{
	return monsters;
}

bool Dungeon::EncounterMonster(Player* player, Monster* monster)
{
	string strEncounterText = "[System] " + monster->GetCharacterInfo().strCharacterName + "과(와) 조우했습니다!";
	Dialogue::ShowOption(strEncounterText);

	//TODO : 전투 로직 _ 둘의 Agility를 비교하여 먼저 공격하는 캐릭터 결정
	int16_t iPlayerAgility = player->GetCharacterInfo().characterStats.GetAgility();
	int16_t iMonsterAgility = monster->GetCharacterInfo().characterStats.GetAgility();

	bool bIsPlayerTurn = iPlayerAgility >= iMonsterAgility;
	bool bIsBattleOver = false;

	int32_t iPlayerHealth = player->GetCharacterInfo().iCurrentHealth;
	int32_t iMonsterHealth = monster->GetCharacterInfo().iCurrentHealth;
	while (iPlayerHealth > 0 && monster->GetCharacterInfo().iCurrentHealth > 0 && !bIsBattleOver)
	{
		if (bIsPlayerTurn)
		{
			string battleText = "1. " + monster->GetCharacterInfo().strCharacterName + "를(을) 공격한다!! \n2. 이대로는 위험하다. 도망가자..\n당신의 선택은??";
			Dialogue::ShowOption(battleText);
			int battleChoice;
			cin >> battleChoice;
			if (battleChoice == 1)
			{
				Common::PauseAndClearScreen();
				player->Attack(monster);
			}
			else if (battleChoice == 2)
			{
				// 도망 확률 계산 (예: 50% 확률)
				if (rand() % 2 == 0)
				{
					cout << "\n===========================================\n";
					cout << "\n[System] 당신은 도망에 성공했습니다!\n";
					cout << "\n===========================================\n" << endl;
					bIsBattleOver = true;
					Common::PauseAndClearScreen();
					break;
				}
				else
				{
					cout << "\n===========================================\n";
					cout << "\n[System] 도망에 실패했습니다!\n";
					cout << "\n===========================================\n" << endl;
					Common::PauseAndClearScreen();
				}
			}
		}
		else
		{
			monster->Attack(player);
		}

		// 턴 교대
		bIsPlayerTurn = !bIsPlayerTurn;
		
	}

	// 결과 출력
	if (!bIsBattleOver)
	{
		if (player->GetCharacterInfo().iCurrentHealth <= 0)
		{
			cout << "\n===========================================\n";
			cout << "\n[System] " << player->GetCharacterInfo().strCharacterName << "이(가) 쓰러졌습니다.\n";
			cout << "\n[System] 게임 오버입니다. 마을로 돌아갑니다.\n";
			cout << "\n===========================================\n" << endl;
			Common::PauseAndClearScreen();
			return false;
		}
		else if (monster->GetCharacterInfo().iCurrentHealth <= 0)
		{
			//TODO :몬스터 처치시 출력되는 내용 옮기기
		}
	}
	return true;
}

Dungeon::~Dungeon()
{
	stages.clear();
}
