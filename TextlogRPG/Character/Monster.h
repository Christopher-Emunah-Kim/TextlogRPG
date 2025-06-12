#pragma once
#include "BaseCharacter.h"
#include "CharacterInfo.h"
#include "../Character/Component/MonsterStatusComponent.h"
#include "../Character/Component/MonsterCombatComponent.h"
#include "../Character/Component/MonsterDropComponent.h"

class Item;

class Monster : public BaseCharacter
{
public:
	// User-Defined Constructor for Monster creation
	Monster(const FMonsterInfo& info);
	// Destructor
	~Monster();

private:
	int32 dropExperience;
	int32 dropGold;
	FMonsterInfo fMonsterInfo;
	//vector<Item*> dropItems; // weapon, armor, misc items
	vector<string> dropItemNames;

	int32 lastCalculatedDamage;
	bool isDefeated;
	Item* lastDropItem;

private:
	MonsterStatusComponent m_monsterStatusComp;
	MonsterCombatComponent m_monsterCombatComp;
	MonsterDropComponent   m_monsterDropComp;

public:
	MonsterStatusComponent& GetMonsterStatusComponent() { return m_monsterStatusComp; }



	// Override functions
	virtual const FCharacterInfo& GetCharacterInfo() const override { return fMonsterInfo; }
	virtual void ApplyDamageFrom(BaseCharacter& attacker) override;
	virtual void Attack(BaseCharacter* target) override;

	void SetCurrentHealth(int32 health);
	void Initialize(const FMonsterInfo& info);

	//Update
	void UpdateDamage(BaseCharacter& attacker);
	void UpdateAttack(BaseCharacter* target);
	bool ProcessItemDrop(Player* playerTarget);

	//Render
	void RenderDamageResult();
	void RenderAttackMessage();
	void RenderItemDropResult(Item* droppedItem, bool isSuccessful, Player* attacker);
	void RenderMonsterStatus() const;

	// Check field
	inline bool isDefeat() const { return isDefeated; }
	inline int32 GetDropExperience() const { return dropExperience; }
	inline int32 GetDropGold() const { return dropGold; }



};
