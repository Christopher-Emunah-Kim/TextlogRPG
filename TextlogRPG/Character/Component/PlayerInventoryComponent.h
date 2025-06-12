#pragma once
#include "IComponent.h"
#include "../../Core/InventoryManager.h"
#include "../../Util/Common.h"

class Player;
class BaseCharacter;


class PlayerInventoryComponent : public IInventoryComponent
{
public:
    PlayerInventoryComponent(Player* owner = nullptr);

    virtual ~PlayerInventoryComponent() = default;
    
private:
	class Player* m_owner;
	InventoryManager m_inventoryManager;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(BaseCharacter* owner) override;
    
public:
    virtual void AddItem(Item* item) override;
    virtual void RemoveItem(Item* item) override;
    virtual list<Item*> GetItemsByType(EItemType type) const override;
    virtual const list<Item*>& GetAllItems() const override;

    virtual void RenderItemAdded(Item* item) override;
    virtual void RenderItemRemoved(Item* item) override;
    
};