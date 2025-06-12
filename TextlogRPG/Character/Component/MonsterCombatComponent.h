#pragma once
#include "IComponent.h"

class Monster;
class BaseCharacter;

class MonsterCombatComponent : public ICombatComponent
{
public:
    MonsterCombatComponent(Monster* owner = nullptr);
    virtual ~MonsterCombatComponent();

private:
	Monster* m_owner;
	int32 m_lastCalculatedDamage;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(BaseCharacter* owner);
    
public:
    virtual void Attack(BaseCharacter* target) override;
    virtual void ApplyDamageFrom(BaseCharacter& attacker) override;
    virtual int32 CalculateDamageFrom(const FCharacterInfo& targetCharacterInfo) override;
    virtual int32 UpdateDamage(BaseCharacter& attacker) override;
    virtual void UpdateAttack(BaseCharacter* target) override;
    virtual void RenderAttackMessage(BaseCharacter* target) override;
    virtual void RenderDamageResult(BaseCharacter& attacker, int32 damage) override;


	// Don't Use virtual functions
#pragma region UNUSED FUNCS
    virtual void DisplayDeathMessage() override {}
    virtual void DisplayDamageMessage(BaseCharacter& attacker, int32 damage) override {}
#pragma endregion

};