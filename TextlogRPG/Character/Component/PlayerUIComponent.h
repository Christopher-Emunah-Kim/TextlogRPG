#pragma once
#include "IComponent.h"


class Player;

class PlayerUIComponent : public IUIComponent
{
public:
    PlayerUIComponent(Player* owner = nullptr);
    virtual ~PlayerUIComponent() = default;

private:
	class Player* m_owner;

public:

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(Player* owner) override;
    
public:

    virtual void RenderPlayerStatus() const override;
    virtual string BuildPlayerStatusString() const override;
    virtual string BuildBasicInfoString() const override;
    virtual string BuildStatsString() const override;
    virtual string BuildEquipInfoString() const override;
    virtual string BuildInventoryString() const override;
    
};