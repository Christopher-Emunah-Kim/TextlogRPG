#pragma once
#include "IComponent.h"
#include "../../Util/Common.h"

class Monster;

class MonsterStatusComponent : public IStatusComponent
{
public:
    MonsterStatusComponent(Monster* owner = nullptr);
    virtual ~MonsterStatusComponent();


private:
	Monster*	m_owner;
	bool		m_isDefeated;


public:
    virtual void	Initialize() override;
    virtual void	Update() override;
    virtual void	SetOwner(BaseCharacter* owner) override;


public:
    void			SetCurrentHealth(int32 health);
    void			RenderMonsterStatus() const;
    void			RenderDamageResult(int32 damage);

    bool			IsDefeated() const { return m_isDefeated; }


    // Don't Use virtual functions
#pragma region UNUSED FUNCS
    virtual void	ApplyHealing(int32 healAmount) override {}
    virtual void	CharacterLevelUp() override {}
    virtual void	ProcessBonusStatusSelection() override {}
    virtual void	ApplyStatusBonus(char, int16&, int16&, int16&) override {}
    virtual void	IncrementLevel() override {}
    virtual void	UpdateLevelDataPerLevel() override {}
    virtual void	UpdateFinalStatus() override {}
    virtual void	RenderLevelUpResult() override {}
    virtual void	RenderBonusStatusPrompt() override {}
#pragma endregion

};