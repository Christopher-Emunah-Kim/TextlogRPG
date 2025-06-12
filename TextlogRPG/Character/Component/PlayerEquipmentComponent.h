#pragma once
#include "IComponent.h"
#include "../../Core/EquipmentManager.h"
#include "../CharacterStatus.h"

class Player;
class BaseCharacter;
class Item;

class PlayerEquipmentComponent : public IEquipmentComponent
{
public:
	PlayerEquipmentComponent(Player* owner = nullptr);
	virtual ~PlayerEquipmentComponent() = default;

private:
	class Player* m_owner;
	EquipmentManager m_equipmentManager;
	CharacterStatus m_equipmentStatus;

public:
    
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(BaseCharacter* owner) override;
    
public:

    virtual void EquipItem(Item* item) override;
    virtual void UnequipItem(Item* item) override;
    virtual void UpdateEquipmentStatus() override;
    virtual Item* HandlePreviousEquipItem(Item* item) override;
    virtual void HandleMiscItem(Item* item) override;
    virtual const EquipmentManager& GetEquipmentManager() const override;
    virtual void RenderEquipMessage(Item* newItem) override;
    virtual void RenderMiscItemAdded(Item* item) override;
    
public:

    inline CharacterStatus GetEquipmentStatus() const { return m_equipmentStatus; }
    void UpdateEquipItem(Item* previousItem, Item* newItem);
};