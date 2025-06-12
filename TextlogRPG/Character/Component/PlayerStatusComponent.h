#pragma once
#include "IComponent.h"
#include "../CharacterStatus.h"

class Player;

class PlayerStatusComponent : public IStatusComponent
{
public:
    PlayerStatusComponent(Player* owner = nullptr);
    virtual ~PlayerStatusComponent() = default;
    
private:
	Player* m_owner;
	CharacterStatus m_baseStatus;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(Player* owner) override;
    

public:
    virtual void Heal(int32 healAmount) override;
    virtual void CharacterLevelUp() override;
    virtual void ProcessBonusStatusSelection() override;
    virtual void ApplyStatusBonus(char statusChoice, int16& playerAtk, int16& playerDef, int16& playerAgi) override;
    virtual void IncrementLevel() override;
    virtual void UpdateLevelDataPerLevel() override;
    virtual void UpdateFinalStatus() override;
    virtual void RenderLevelUpResult() override;
    virtual void RenderBonusStatusPrompt() override;
    

public:
    CharacterStatus GetBaseStatus() const { return m_baseStatus; }
    void SetBaseStatus(const CharacterStatus& status) { m_baseStatus = status; }
    void UpdateBonusStatus(char statusChoice);
};