#include "MonsterCombatComponent.h"
#include "MonsterStatusComponent.h"
#include "../Monster.h"

MonsterCombatComponent::MonsterCombatComponent(Monster* owner)
    : m_owner(owner), m_lastCalculatedDamage(0)
{
}

MonsterCombatComponent::~MonsterCombatComponent()
{
}

void MonsterCombatComponent::Initialize()
{
    m_lastCalculatedDamage = 0;
}

void MonsterCombatComponent::Update()
{
}

void MonsterCombatComponent::SetOwner(BaseCharacter* owner)
{
	m_owner = dynamic_cast<Monster*>(owner);
}

void MonsterCombatComponent::Attack(BaseCharacter* target)
{
	if (target == nullptr || m_owner == nullptr)
	{
		Common::PrintErrorMsg("오류 발생. 공격할 수 없습니다.");
		return;
	}
    
    RenderAttackMessage(target);
    UpdateAttack(target);
}

void MonsterCombatComponent::ApplyDamageFrom(BaseCharacter& attacker)
{
    if (m_owner==nullptr) 
		return;

    m_lastCalculatedDamage = UpdateDamage(attacker);
    
    // 데미지 결과 렌더링은 MonsterStatusComponent에서 처리
	MonsterStatusComponent& statusComp = m_owner->GetMonsterStatusComponent();
    
	statusComp.RenderDamageResult(m_lastCalculatedDamage);
    
    Common::PauseAndClearScreen(2000);
}

int32 MonsterCombatComponent::CalculateDamageFrom(const FCharacterInfo& targetCharacterInfo)
{
	if (m_owner == nullptr)
	{
		return 0;
	}
    
    const FCharacterInfo& monsterInfo = m_owner->GetCharacterInfo();
    return monsterInfo.characterStats.CalculateDamage(targetCharacterInfo.characterStats);
}

int32 MonsterCombatComponent::UpdateDamage(BaseCharacter& attacker)
{
	if (m_owner == nullptr)
	{
		return 0;
	}
    
    const FCharacterInfo& attackerInfo = attacker.GetCharacterInfo();
    int32 damage = CalculateDamageFrom(attackerInfo);
    
    // 몬스터 체력 업데이트
	MonsterStatusComponent& statusComp = m_owner->GetMonsterStatusComponent();
    
	const FCharacterInfo& monsterInfo = m_owner->GetCharacterInfo();

	int32 currentHealth = monsterInfo.iCurrentHealth;
	int32 calculatedHealth = currentHealth - damage;
	m_owner->SetCurrentHealth(calculatedHealth);

	if (monsterInfo.iCurrentHealth <= 0)
	{
		statusComp.SetCurrentHealth(0);
	}
    
    return damage;
}

void MonsterCombatComponent::UpdateAttack(BaseCharacter* target)
{
    if (target && m_owner)
    {
        target->ApplyDamageFrom(*m_owner);
    }
}

void MonsterCombatComponent::RenderAttackMessage(BaseCharacter* target)
{
    if (m_owner)
    {
        string msg = m_owner->GetCharacterInfo().strCharacterName + "이(가) 당신을 공격합니다.";
        Common::PrintSystemMsg(msg);
        Common::PauseAndClearScreen(3000);
    }
}

void MonsterCombatComponent::RenderDamageResult(BaseCharacter& attacker, int32 damage)
{
    // MonsterStatusComponent에서 처리
}