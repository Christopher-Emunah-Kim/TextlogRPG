#pragma once
#include "IComponent.h"
#include <vector>
#include <string>

class Monster;
class Player;
class Item;

class MonsterDropComponent : public IComponent
{
public:
    MonsterDropComponent(Monster* owner = nullptr);
    virtual ~MonsterDropComponent();

private:
    Monster* m_owner;
    vector<string> m_dropItemNames;
    Item* m_lastDropItem;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(BaseCharacter* owner) override;

public:
	inline const vector<string>& GetDropItemNames() const { return m_dropItemNames; }
	inline Item* GetLastDropItem() const { return m_lastDropItem; }

public:
    void InitializeDropItems(const vector<string>& itemNames);
    bool ProcessItemDrop(Player* playerTarget);
    void RenderItemDropResult(Item* droppedItem, bool isSuccessful, Player* attacker);

    int32 GetDropExperience() const;
    int32 GetDropGold() const;

};  