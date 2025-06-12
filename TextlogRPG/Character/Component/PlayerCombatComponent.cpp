#include "PlayerCombatComponent.h"
#include "../Player.h"
#include "../BaseCharacter.h"


PlayerCombatComponent::PlayerCombatComponent(Player* owner)
	:m_owner(owner), m_lastCalculatedDamage(0)
{

}

void PlayerCombatComponent::Initialize()  
{  
    if (m_owner)  
    { 
		m_lastCalculatedDamage = 0;
    }  
}

void PlayerCombatComponent::Update()
{

}

void PlayerCombatComponent::SetOwner(Player* owner)
{
	m_owner = owner;
}

void PlayerCombatComponent::Attack(BaseCharacter* target)
{
	if (target == nullptr)
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
		return;
	}

	RenderAttackMessage(target);
	UpdateAttack(target);
}

void PlayerCombatComponent::ApplyDamageFrom(BaseCharacter& attacker)
{
	int32 iCalculatedDamage = UpdateDamage(attacker);
	RenderDamageResult(attacker, iCalculatedDamage);
}

int32 PlayerCombatComponent::CalculateDamageFrom(const FCharacterInfo& targetCharacterInfo)
{
	return m_owner->GetCharacterInfo().characterStats.CalculateDamage(targetCharacterInfo.characterStats);
}


int32 PlayerCombatComponent::UpdateDamage(BaseCharacter& attacker)
{
	const FCharacterInfo& fTargetCharacterInfo = attacker.GetCharacterInfo();
	int32 iCalculatedDamage = CalculateDamageFrom(fTargetCharacterInfo);

	FPlayerInfo& playerInfo = const_cast<FPlayerInfo&>(m_owner->GetCharacterInfo()); 

	playerInfo.iCurrentHealth -= iCalculatedDamage;

	if (playerInfo.iCurrentHealth <= 0)
	{
		playerInfo.iCurrentHealth = 0; // maintain game-over state
	}

	m_lastCalculatedDamage = iCalculatedDamage;

	return iCalculatedDamage;
}

void PlayerCombatComponent::UpdateAttack(BaseCharacter* target)
{
	if (target != nullptr)
	{
		target->ApplyDamageFrom(*m_owner);
	}
	else
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
	}
}

void PlayerCombatComponent::RenderAttackMessage(BaseCharacter* target)
{
	if (target != nullptr)
	{
		string strAttackText = "당신은 " + target->GetCharacterInfo().strCharacterName + "을(를) 공격합니다.";
		Common::PrintSystemMsg(strAttackText);
		Common::PauseAndClearScreen(2000);
	}
	else
	{
		Common::PrintSystemMsg("공격 대상이 없습니다.");
		Common::PauseAndClearScreen(1000);
	}
}

void PlayerCombatComponent::RenderDamageResult(BaseCharacter& attacker, int32 damage)
{
	if (m_owner->GetCharacterInfo().iCurrentHealth <= 0)
	{
		DisplayDeathMessage();
	}
	else
	{
		DisplayDamageMessage(attacker, damage);
	}
	Common::PauseAndClearScreen(2000);
}

void PlayerCombatComponent::DisplayDeathMessage()
{
	Common::PrintSystemMsg("당신은 여신의 곁으로 돌아갑니다..");
}

void PlayerCombatComponent::DisplayDamageMessage(BaseCharacter& attacker, int32 damage)
{
	string strDamageText = attacker.GetCharacterInfo().strCharacterName + "에게 " +
		to_string(damage) + "의 데미지를 입었습니다.\n당신의 현재 체력 : " +
		to_string(m_owner->GetCharacterInfo().iCurrentHealth);
	Common::PrintSystemMsg(strDamageText);
}