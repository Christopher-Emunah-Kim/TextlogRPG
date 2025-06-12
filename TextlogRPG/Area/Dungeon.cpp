#include "Dungeon.h"
#include "../Character/Player.h"
#include "../Character/Monster.h"
#include "../Util/Dialogue.h"
#include "../Util/EGameState.h"

Dungeon::Dungeon()
{
	vecDungeonMonsters.clear();
	vecDungeonStages.clear();
	currentStageIndex = 0;
}

Dungeon::Dungeon(const vector<vector<FMonsterInfo>>& stageMonsterInfo)
{
	for (size_t i = 0; i < stageMonsterInfo.size(); ++i)
	{
		const vector<FMonsterInfo>& monsterInfos = stageMonsterInfo[i];
		vecDungeonStages.emplace_back(new DungeonStage(monsterInfos));
	}
	currentStageIndex = 0;
}

Dungeon::~Dungeon()
{
	for (vector<DungeonStage*>::iterator it = vecDungeonStages.begin(); it != vecDungeonStages.end(); ++it)
	{
		DungeonStage* stage = *it;
		if (stage) 
		{
			delete stage;
		}
	}
	vecDungeonStages.clear();

	// 몬스터 정리
	for (vector<Monster*>::iterator it = vecDungeonMonsters.begin(); it != vecDungeonMonsters.end(); ++it )
	{
		Monster* monster = *it;
		if (monster) 
		{
			delete monster;
		}
	}
	vecDungeonMonsters.clear();
}


DungeonStage* Dungeon::GetCurrentStage() const
{
	if (currentStageIndex < vecDungeonStages.size())
	{
		return vecDungeonStages[currentStageIndex];
	}
	return nullptr;
}

bool Dungeon::IsMoreStageLeft()
{
	if (currentStageIndex + 1 < vecDungeonStages.size())
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

void Dungeon::Initialize(Player* player)
{
	if (vecDungeonStages.empty())
	{
		CreateDungeonStages();
	}
	else
	{
		Common::PrintSystemMsg("당신을 위한 던전 스테이지가 준비되어 있습니다.");
	}

	if (player == nullptr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. 던전 탐험을 시작할 수 없습니다.");
		return;
	}
}

EGameState Dungeon::Process(Player* player)
{
	Enter(player);

	char dungeonChoice = Common::GetCharInput();
	Common::PauseAndClearScreen();

	return HandleChoice(dungeonChoice, player);
}

void Dungeon::Clear()
{

}

void Dungeon::AddMonster(Monster* monster) 
{
	if (monster == nullptr)
	{
		Common::PrintErrorMsg("몬스터 정보가 없습니다. AddMonster를 중단합니다.");
		return;
	}
	vecDungeonMonsters.push_back(monster);
}

void Dungeon::RemoveMonster(Monster* monster) 
{
	if (monster == nullptr)
	{
		Common::PrintErrorMsg("몬스터 정보가 없습니다. RemoveMonster를 중단합니다.");
		return;
	}
	vecDungeonMonsters.erase(remove(vecDungeonMonsters.begin(), vecDungeonMonsters.end(), monster), vecDungeonMonsters.end());
}

vector<Monster*>& Dungeon::GetMonsterList()
{
	return vecDungeonMonsters;
}

void Dungeon::CreateDungeonStages()
{
	// Reset the settings
	for (vector<DungeonStage*>::iterator it = vecDungeonStages.begin(); it != vecDungeonStages.end(); ++it) 
	{
		DungeonStage* stage = *it;
		if (stage)
		{
			delete stage;
		}
	}
	vecDungeonStages.clear();
	currentStageIndex = 0;

	//Generate Monster Lists(info)
	vector<FMonsterInfo> stage1 = {
		FMonsterInfo(CharacterStatus::NewStatus(6, 3, 6), 18, 18, 2, "허약한 고블린", 20, 10),
		FMonsterInfo(CharacterStatus::NewStatus(5, 4, 5), 20, 20, 2, "허약한 슬라임", 22, 12),
		FMonsterInfo(CharacterStatus::NewStatus(7, 4, 7), 22, 22, 3, "허약한 스켈레톤", 28, 15),
	};

	vector<FMonsterInfo> stage2 = {
		FMonsterInfo(CharacterStatus::NewStatus(12, 7, 10), 35, 35, 5, "허약한 오크", 40, 25),
		FMonsterInfo(CharacterStatus::NewStatus(15, 8, 12), 40, 40, 6, "허약한 드래곤", 60, 40),
		FMonsterInfo(CharacterStatus::NewStatus(16, 9, 11), 38, 38, 5, "강력한 고블린", 45, 30),
		FMonsterInfo(CharacterStatus::NewStatus(15, 8, 10), 39, 39, 5, "강력한 슬라임", 45, 30),
	};

	vector<FMonsterInfo> stage3 = {
		FMonsterInfo(CharacterStatus::NewStatus(22, 13, 15), 60, 60, 8, "강력한 스켈레톤", 80, 50),
		FMonsterInfo(CharacterStatus::NewStatus(25, 15, 16), 70, 70, 9, "강력한 오크", 90, 60),
		FMonsterInfo(CharacterStatus::NewStatus(28, 16, 18), 80, 80, 10, "완전 강력한 스켈레톤", 120, 80),
		FMonsterInfo(CharacterStatus::NewStatus(32, 18, 20), 90, 90, 12, "완전 강력한 고블린", 150, 100),
		FMonsterInfo(CharacterStatus::NewStatus(36, 20, 22), 100, 100, 13, "완전 강력한 슬라임", 180, 120),
		FMonsterInfo(CharacterStatus::NewStatus(40, 22, 25), 110, 110, 15, "완전 강력한 드래곤", 250, 180),
	};

	vector<vector<FMonsterInfo>> dungeonStages = { stage1, stage2, stage3 };

	//Generate new Dungeon
	for (size_t i = 0; i < dungeonStages.size(); ++i)
	{
		const vector<FMonsterInfo>& monsterInfos = dungeonStages[i];
		vecDungeonStages.emplace_back(new DungeonStage(monsterInfos));
	}
}

EGameState Dungeon::HandleChoice(char dungeonChoice, Player* player)
{
	switch (dungeonChoice)
	{
	case '1': 
	{
		return ProcessBattleChoice(player);
	}
	case '2':
	{
		RenderRunChoice();
		return EGameState::VILLAGE;
	}

	default: 
	{
		RenderWrongChoice();
		return EGameState::DUNGEON;
	}
	}
}

EGameState Dungeon::ProcessBattleChoice(Player* player)
{
	while (true)
	{
		DungeonStage* stage = GetCurrentStage();
		if (stage == nullptr)
		{
			Common::PrintSystemMsg("유효한 던전 스테이지가 존재하지 않습니다.\n마을로 돌아갑니다.");
			return EGameState::VILLAGE;
		}

		vector<Monster*> stageMonsterList = stage->GetMonsters();
		if (stageMonsterList.empty())
		{
			stage->EnterStage();
			stageMonsterList = stage->GetMonsters();
		}

		while (true)
		{
			// 몬스터가 모두 죽었는지 확인
			bool allMonstersDead = true;
			for (size_t i = 0; i < stageMonsterList.size(); ++i)
			{
				Monster* mon = stageMonsterList[i];
				if (mon->GetCharacterInfo().iCurrentHealth > 0)
				{
					allMonstersDead = false;
					break;
				}
			}

			if (allMonstersDead)
			{
				if (IsMoreStageLeft())
				{
					Common::PrintSystemMsg("다음 스테이지로 진입합니다");
					Common::PauseAndClearScreen();
					stage = GetCurrentStage();
					stage->EnterStage();
					stageMonsterList = stage->GetMonsters();
					continue;
				}
				else
				{
					Common::PrintSystemMsg("모든 던전 스테이지를 클리어했습니다.\n마을로 돌아갑니다..");
					Common::PauseAndClearScreen();
					return EGameState::VILLAGE;
				}
			}

			Common::PrintSystemMsg("정말 이 스테이지를 도전하시겠습니까?\n\n1. 멈출 수 없다. 앞으로 나아가자.\n\n2. 목숨은 소중하니까, 도망간다(마을로 복귀)");
			char stageChoice = Common::GetCharInput();

			Common::PauseAndClearScreen();

			if (stageChoice == '2')
			{
				Common::PrintSystemMsg("던전에서 도망쳤습니다. 마을로 돌아갑니다.");
				Common::PauseAndClearScreen();
				return EGameState::VILLAGE;
			}

			// 몬스터와 전투
			EGameState battleResult = BattleInStage(stageMonsterList, stage, player);

			// 전투 결과에 따라 처리
			if (battleResult == EGameState::VILLAGE || battleResult == EGameState::GAME_OVER)
				return battleResult;
		}
	}
}

void Dungeon::RenderRunChoice()
{
	Common::PrintSystemMsg("무모한 도전이 반드시 정답은 아닙니다.\n던전 탐험을 중단하고 마을로 돌아갑니다.");
	Common::PauseAndClearScreen();
}

void Dungeon::RenderWrongChoice()
{
	Common::PrintErrorMsg("잘못된 입력입니다.");
	Common::PrintErrorMsg("던전에 재입장합니다..");
	Common::PauseAndClearScreen();
}

EGameState Dungeon::BattleInStage(const vector<Monster*>& monsters, DungeonStage* stage, Player* player)
{
	// 랜덤 시드 설정
	srand(static_cast<unsigned int>(time(NULL)));

	while (true)
	{
		// 살아있는 몬스터만 필터링
		vector<Monster*> aliveMonsters;
		for (size_t i = 0; i < monsters.size(); ++i)
		{
			Monster* mon = monsters[i];
			if (mon->GetCharacterInfo().iCurrentHealth > 0)
				aliveMonsters.push_back(mon);
		}

		// 모든 몬스터가 죽었으면 종료
		if (aliveMonsters.empty())
			break;

		// 랜덤 몬스터 선택
		size_t randomIndex = rand() % aliveMonsters.size();
		Monster* randomMonster = aliveMonsters[randomIndex];

		// 전투 수행
		EBattleResult result = EncounterMonster(player, randomMonster);

		// 전투 결과 처리
		switch (result)
		{
		case EBattleResult::PLAYER_DEAD:
			RenderGameOverMsg();
			return EGameState::GAME_OVER;
		case EBattleResult::PLAYER_RUN:
			return EGameState::VILLAGE;
		case EBattleResult::PLAYER_WIN:
			stage->OnMonsterDefeat(randomMonster);
			break;

		default:
			Common::PrintErrorMsg("전투 중 알 수 없는 오류가 발생했습니다.");
			return EGameState::VILLAGE;
		}
	}

	return EGameState::DUNGEON; // 계속 던전 진행
}

void Dungeon::RenderGameOverMsg()
{
	Common::PrintSystemMsg("게임이 종료되었습니다.\n다시 시작하려면 게임을 재실행해주세요.");
	Common::PauseAndClearScreen();
}

EBattleResult Dungeon::EncounterMonster(Player* player, Monster* monster)
{
	
	Common::PrintSystemMsg(monster->GetCharacterInfo().strCharacterName + "과(와) 조우했습니다!");
	monster->RenderMonsterStatus();
	Common::PauseAndClearScreen(300);


	if (!player || !monster)
	{
		Common::PrintErrorMsg("플레이어 또는 몬스터 정보가 없습니다. 전투를 종료합니다.");
		return EBattleResult::_ERROR;
	}

	int16 iPlayerAgility = player->GetCharacterInfo().characterStats.GetAgility();
	int16 iMonsterAgility = monster->GetCharacterInfo().characterStats.GetAgility();

	bool bIsPlayerTurn = iPlayerAgility >= iMonsterAgility;

	
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
				player->RenderPlayerStatus();
				continue;
			} 
			break;
			case '3':
			{
				if (rand() % 3 == 0)
				{
					Common::PrintSystemMsg("당신은 필사적으로 도망쳤지만, 몬스터가 뛰어올라 당신의 앞을 가로막습니다.\n몬스터가 당신을 공격합니다!");
					Common::PauseAndClearScreen();
				}
				else
				{
					Common::PrintSystemMsg("몬스터가 당신을 쫓아왔지만, 당신은 무사히 던전 입구로 도망쳤습니다.");
					Common::PauseAndClearScreen();
					return EBattleResult::PLAYER_RUN;
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

