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
	for (size_t i = 0; i < stageMonsterInfo.size(); ++i)
	{
		const vector<FMonsterInfo>& monsterInfos = stageMonsterInfo[i];
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

bool Dungeon::IsMoreStageLeft()
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
	if (player == nullptr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. EnterDungeon을 중단합니다.");
		return;
	}

	Common::PrintSystemMsg("던전 탐험을 시작합니다.");
	Common::PrintSystemMsg("기억하십시오. 심연을 들여다볼수록,\n 당신 또한 심연에 물들 것입니다.");
	Common::PauseAndClearScreen(2500);

	Common::ShowOption("[System] 던전의 입구에 도착했습니다. 도전하시겠습니까?\n\n1. 인생은 모험이지!\n2. 아니 지금은 아닌것 같아.(마을로 돌아간다)");
}

void Dungeon::AddMonster(Monster* monster) 
{
	if (monster == nullptr)
	{
		Common::PrintErrorMsg("몬스터 정보가 없습니다. AddMonster를 중단합니다.");
		return;
	}
	monsters.push_back(monster);
}

void Dungeon::RemoveMonster(Monster* monster) 
{
	if (monster == nullptr)
	{
		Common::PrintErrorMsg("몬스터 정보가 없습니다. RemoveMonster를 중단합니다.");
		return;
	}
	monsters.erase(remove(monsters.begin(), monsters.end(), monster), monsters.end());
}

vector<Monster*>& Dungeon::GetMonsterList() 
{
	return monsters;
}

EBattleResult Dungeon::EncounterMonster(Player* player, Monster* monster)
{
	
	Common::PrintSystemMsg(monster->GetCharacterInfo().strCharacterName + "과(와) 조우했습니다!");
	monster->ShowMonsterStatus();


	if (!player || !monster)
	{
		Common::PrintErrorMsg("플레이어 또는 몬스터 정보가 없습니다. 전투를 종료합니다.");
		return EBattleResult::_ERROR;
	}

	//TODO : 전투 로직 _ 둘의 Agility를 비교하여 먼저 공격하는 캐릭터 결정
	int16 iPlayerAgility = player->GetCharacterInfo().characterStats.GetAgility();
	int16 iMonsterAgility = monster->GetCharacterInfo().characterStats.GetAgility();

	bool bIsPlayerTurn = iPlayerAgility >= iMonsterAgility;
	//bool bIsBattleOver = false;

	
	while (true)
	{
		const int32& iPlayerHealth = player->GetCharacterInfo().iCurrentHealth;
		const int32& iMonsterHealth = monster->GetCharacterInfo().iCurrentHealth;
		if (iPlayerHealth <= 0 || iMonsterHealth <= 0)
		{
			break;
		}

		Common::PauseAndClearScreen(1500);
		if (bIsPlayerTurn)
		{
			Common::ShowOption("1. " + monster->GetCharacterInfo().strCharacterName + "를(을) 공격한다!! \n\n2. 내 상태가 어떤지 확인해보자\n\n3. 이대로는 위험하다. 도망가자..\n\n당신의 선택은??");
			char battleChoice = Common::GetCharInput();

			switch (battleChoice)
			{
			case '1':
			{
				Common::PauseAndClearScreen();

				Common::PrintSystemMsg(player->GetCharacterInfo().strCharacterName + "이(가) 공격할 차례입니다.");
				player->Attack(monster);
			}
			break;
			case '2':
			{
				Common::PauseAndClearScreen(500);
				player->ShowPlayerStatus();
				continue;
			} 
			break;
			case '3':
			{
				// 도망 확률 계산 (예: 50% 확률)
				if (rand() % 2 == 0)
				{
					Common::PrintSystemMsg("몬스터가 당신을 쫓아왔지만, 당신은 무사히 던전 입구로 도망쳤습니다.");
					Common::PauseAndClearScreen();
					return EBattleResult::PLAYER_RUN;
				}
				else
				{
					Common::PrintSystemMsg("당신은 필사적으로 도망쳤지만, 몬스터가 뛰어올라 당신의 앞을 가로막습니다.");
					Common::PauseAndClearScreen();
				}
			}
			break;

			default :
			{
				Common::PrintSystemMsg("어이쿠 손이 미끄러졌네!\n" + monster->GetCharacterInfo().strCharacterName + "를(을) 공격한다!!");
				player->Attack(monster);
			}
			}
		}
		else
		{
			Common::PrintSystemMsg(monster->GetCharacterInfo().strCharacterName + "이(가) 공격할 차례입니다.");
			monster->Attack(player);
		}

		// 턴 교대
		bIsPlayerTurn = !bIsPlayerTurn;
		
	}

	// 결과 출력
	if (player->GetCharacterInfo().iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg(player->GetCharacterInfo().strCharacterName + "이(가) 쓰러졌습니다.\n[System] 당신은 여신의 가호 아래 마을로 돌아갑니다.");
		Common::PauseAndClearScreen();
		return EBattleResult::PLAYER_DEAD;
	}
	else if (monster->GetCharacterInfo().iCurrentHealth <= 0)
	{
		Common::PrintSystemMsg(monster->GetCharacterInfo().strCharacterName + "을(를) 처치했습니다!");
		Common::PauseAndClearScreen();
		return EBattleResult::PLAYER_WIN;
	}
	return EBattleResult::_ERROR;
}

Dungeon::~Dungeon()
{
	stages.clear();
}
