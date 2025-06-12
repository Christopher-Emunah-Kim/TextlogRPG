#include "PlayerStatusComponent.h"
#include "../Player.h"
#include "../../LevelData/LevelData.h"
#include "PlayerEquipmentComponent.h"

PlayerStatusComponent::PlayerStatusComponent(Player* owner)
    : m_owner(owner), m_baseStatus(CharacterStatus::NewStatus(0, 0, 0))
{
}

void PlayerStatusComponent::Initialize()
{
	m_baseStatus = m_owner->GetCharacterInfo().characterStats;
}

void PlayerStatusComponent::Update()
{
   
}

void PlayerStatusComponent::SetOwner(BaseCharacter* owner)
{
	m_owner = dynamic_cast<Player*>(owner);
}

void PlayerStatusComponent::Heal(int32 healAmount)
{
    if (healAmount <= 0)
        return;

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    playerInfo.iCurrentHealth += healAmount;

    if (playerInfo.iCurrentHealth > playerInfo.iMaxHealth)
    {
        playerInfo.iCurrentHealth = playerInfo.iMaxHealth;
    }
}

void PlayerStatusComponent::CharacterLevelUp()
{
    IncrementLevel();

    FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    if (playerInfo.iCurrentLevel > DEFAULT_CHARACTER_MAX_LEVEL)
    {
        playerInfo.iCurrentLevel = DEFAULT_CHARACTER_MAX_LEVEL;
        return;
    }

    UpdateLevelDataPerLevel();
    ProcessBonusStatusSelection();
    RenderLevelUpResult();
}

void PlayerStatusComponent::ProcessBonusStatusSelection()
{
    RenderBonusStatusPrompt();
    char statusChoice = Common::GetCharInput();
    UpdateBonusStatus(statusChoice);
}

void PlayerStatusComponent::ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi)
{
    switch (statusChoice)
    {
    case '1':
        playerAtk += LEVELUP_BONUS;
        break;
    case '2':
        playerDef += LEVELUP_BONUS;
        break;
    case '3':
        playerAgi += LEVELUP_BONUS;
        break;
    default:
        break;
    }
}

void PlayerStatusComponent::IncrementLevel()
{
	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    playerInfo.iCurrentLevel++;
}

void PlayerStatusComponent::UpdateLevelDataPerLevel()
{
    LevelData levelDataInstance;
	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    FLevelProperties levelData = levelDataInstance.GetLevelData(playerInfo.iCurrentLevel);
    
    playerInfo.iMaxHealth = levelData.maxHealthPerLevel;
    playerInfo.playerMaxExperience = levelData.maxExperiencePerLevel;
    playerInfo.iCurrentHealth = playerInfo.iMaxHealth; // 레벨업 후 체력 최대치로 회복
}

void PlayerStatusComponent::UpdateFinalStatus()
{
    // 장비 컴포넌트에서 장비 스탯 가져오기
	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());

	const PlayerEquipmentComponent* equipComp = &m_owner->GetEquipmentComponent();

	if (equipComp != nullptr)
	{
		CharacterStatus equipmentStatus = equipComp->GetEquipmentStatus();
		// 최종 스탯 계산
		playerInfo.characterStats = CharacterStatus::NewStatus(
			m_baseStatus.GetAttack() + equipmentStatus.GetAttack(),
			m_baseStatus.GetDefense() + equipmentStatus.GetDefense(),
			m_baseStatus.GetAgility() + equipmentStatus.GetAgility()
		);
	}
}

void PlayerStatusComponent::RenderLevelUpResult()
{
    Common::PauseAndClearScreen(300);

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo());
    string strLevelUpMsg = "레벨업 결과 보기\n현재 레벨 : " + to_string(playerInfo.iCurrentLevel) + "\n"
        + "체력 : " + to_string(playerInfo.iCurrentHealth) + "/" + to_string(playerInfo.iMaxHealth) + "\n"
        + "공격력 : " + to_string(playerInfo.characterStats.GetAttack()) + "\n"
        + "방어력 : " + to_string(playerInfo.characterStats.GetDefense()) + "\n"
        + "민첩성 : " + to_string(playerInfo.characterStats.GetAgility());

    Common::PrintSystemMsg(strLevelUpMsg);
}

void PlayerStatusComponent::RenderBonusStatusPrompt()
{
    Common::PrintSystemMsg("레벨업!\n추가로 올릴 능력치를 선택하세요 : \n\n1.공격력을 추가로 획득한다.\n2.방어력을 추가로 획득한다.\n3.민첩성을 추가로 획득한다.");
}

void PlayerStatusComponent::UpdateBonusStatus(char statusChoice)
{
    LevelData levelDataInstance;
    FLevelProperties levelData = levelDataInstance.GetLevelData(m_owner->GetCharacterInfo().iCurrentLevel);
    int16 playerAtk = levelData.attackPerLevel;
    int16 playerDef = levelData.defensePerLevel;
    int16 playerAgi = levelData.agilityPerLevel;

    ApplyStatusBonus(statusChoice, playerAtk, playerDef, playerAgi);

    // 캐릭터 스탯 업데이트
	m_baseStatus = CharacterStatus::NewStatus(playerAtk, playerDef, playerAgi);
    UpdateFinalStatus();
}