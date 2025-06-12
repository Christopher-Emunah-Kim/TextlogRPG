#pragma once
#include "IComponent.h"

class Player;

class PlayerLootComponent : public ILootComponent
{
public:
    PlayerLootComponent(Player* owner = nullptr);
    virtual ~PlayerLootComponent() = default;
    
private:
	class Player* m_owner;

public:

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(Player* owner) override;
    
public:
    virtual void AddGold(int32 gold) override;
    virtual void UseGold(int32 cost) override;
    virtual void EarnGold(int32 earnGold) override;
    virtual void GainLoot(int32 experience, int32 gold, Item* item) override;
    virtual void AddExperience(int32 experience) override;
    virtual void ProcessLevelUp() override;
    virtual void UpdateLoot(int32 gold, int32 experience) override;
    virtual void UpdateGold(int32 earnGold) override;
    virtual void RenderGoldChange(int32 earnGold) override;
    virtual void RenderLootResult(int32 experience, int32 gold, Item* item) override;
    

};