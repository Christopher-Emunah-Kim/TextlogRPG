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
	int32 m_dropExperience;
	int32 m_dropGold;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void SetOwner(BaseCharacter* owner) override;

public:
	inline const vector<string>& GetDropItemNames() const { return m_dropItemNames; }
	inline Item* GetLastDropItem() const { return m_lastDropItem; }
	inline int32 GetDropCompExperience() const { return m_dropExperience; }
	inline int32 GetDropCompGold() const {	return 	m_dropGold;	}

public:
    void InitializeDropItems(const vector<string>& itemNames);
	void SetDropValues(int32 experience, int32 gold);
    bool ProcessItemDrop(Player* playerTarget);
    void RenderItemDropResult(Item* droppedItem, bool isSuccessful, Player* attacker);


};  