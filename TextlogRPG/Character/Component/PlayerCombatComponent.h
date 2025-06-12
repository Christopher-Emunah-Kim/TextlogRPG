#pragma once
#include "IComponent.h"

class Player;
class BaseCharacter;

class PlayerCombatComponent : public ICombatComponent
{
public:
	PlayerCombatComponent(class Player* owner = nullptr);
	virtual ~PlayerCombatComponent() = default;

private:
	Player* m_owner;
	int32 m_lastCalculatedDamage;


public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void SetOwner(BaseCharacter* owner) override;

public:
	virtual void Attack(BaseCharacter* target) override;
	virtual void ApplyDamageFrom(BaseCharacter& attacker) override;
	virtual int32 CalculateDamageFrom(const FCharacterInfo& targetCharacterInfo) override;
	virtual int32 UpdateDamage(BaseCharacter& attacker) override;
	virtual void UpdateAttack(BaseCharacter* target) override;

	
	virtual void RenderAttackMessage(BaseCharacter* target) override;
	virtual void RenderDamageResult(BaseCharacter& attacker, int32 damage) override;
	virtual void DisplayDeathMessage() override;
	virtual void DisplayDamageMessage(BaseCharacter& attacker, int32 damage) override;
};

