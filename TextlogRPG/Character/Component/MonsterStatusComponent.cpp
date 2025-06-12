#include "MonsterStatusComponent.h"
#include "../Monster.h"
#include "../../Core/InputManager.h"

MonsterStatusComponent::MonsterStatusComponent(Monster* owner)
    : m_owner(owner), m_isDefeated(false)
{
}

MonsterStatusComponent::~MonsterStatusComponent()
{
}

void MonsterStatusComponent::Initialize()
{
    m_isDefeated = false;
}

void MonsterStatusComponent::Update()
{

}

void MonsterStatusComponent::SetOwner(BaseCharacter* owner)  
{  
    m_owner = dynamic_cast<Monster*>(owner);  
}

void MonsterStatusComponent::SetCurrentHealth(int32 health)
{
    if (m_owner)
    {
		const FMonsterInfo& monsterInfo = static_cast<const FMonsterInfo&>(m_owner->GetCharacterInfo());

		m_owner->SetCurrentHealth(health);
        if (monsterInfo.iCurrentHealth <= 0)
        {
			m_owner->SetCurrentHealth(0);
            m_isDefeated = true;
        }
        else
        {
            m_isDefeated = false;
        }
    }
}

void MonsterStatusComponent::RenderMonsterStatus() const
{
    if (m_owner)
    {
        const FCharacterInfo& info = m_owner->GetCharacterInfo();
        string strMonsterStatus = " [몬스터 도감] " + info.strCharacterName + " (상세보기)\n"
            + "몬스터 레벨 : " + to_string(info.iCurrentLevel) + "\n"
            + "체력 : " + to_string(info.iCurrentHealth) + "/" + to_string(info.iMaxHealth) + "\n\n"
            + "공격력 : " + to_string(info.characterStats.GetAttack()) + "\n"
            + "방어력 : " + to_string(info.characterStats.GetDefense()) + "\n"
            + "민첩성 : " + to_string(info.characterStats.GetAgility());

        Common::ShowOption(strMonsterStatus);

        cout << "Enter 키를 눌러 계속 진행하세요.\n" << endl;
        InputManager::GetInstance().GetLineInput();
    }
}

void MonsterStatusComponent::RenderDamageResult(int32 damage)
{
    if (m_owner == nullptr) 
		return;
    
    const FCharacterInfo& info = m_owner->GetCharacterInfo();
    
    if (m_isDefeated)
    {
        string strDefeatMsg = info.strCharacterName + "은(는) " + to_string(damage) + "의 데미지를 입었습니다.";
        Common::PrintSystemMsg(strDefeatMsg);

        string strDefeatMesg = "몬스터 " + info.strCharacterName + "이(가) 쓰러졌습니다.";
        Common::PrintSystemMsg(strDefeatMesg);
    }
    else
    {
        string strMsg = info.strCharacterName + "은(는) " + to_string(damage) + "의 데미지를 입었습니다.\n현재 체력: " + to_string(info.iCurrentHealth);
        Common::PrintSystemMsg(strMsg);
    }
}