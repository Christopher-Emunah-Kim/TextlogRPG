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
	
	Monster(const FMonsterInfo& info);
	
	~Monster();

private:
	FMonsterInfo			fMonsterInfo;
	

private:
	MonsterStatusComponent	m_monsterStatusComp;
	MonsterCombatComponent	m_monsterCombatComp;
	MonsterDropComponent	m_monsterDropComp;


public:
	// Override functions
	virtual void					ApplyDamageFrom(BaseCharacter& attacker) override;
	virtual void					Attack(BaseCharacter* target) override;
	virtual const FCharacterInfo&	GetCharacterInfo() const override { return fMonsterInfo; }

	FCharacterInfo&					GetChracterInfoRef() { return fMonsterInfo; }
	

public:
	inline MonsterStatusComponent&	GetMonsterStatusComponent() { return m_monsterStatusComp; }
	inline MonsterCombatComponent&	GetMonsterCombatComponent() { return m_monsterCombatComp; }
	inline MonsterDropComponent&	GetMonsterDropComponent() { return m_monsterDropComp; }


public:
	// status check funcs
	inline bool						isDefeat() const { return m_monsterStatusComp.IsDefeated(); }
	inline int32					GetDropExperience() const { return m_monsterDropComp.GetDropCompExperience(); }
	inline int32					GetDropGold() const { return m_monsterDropComp.GetDropCompGold(); }

public:

	void							SetCurrentHealth(int32 health);
	void							Initialize(const FMonsterInfo& info);
	void							RenderMonsterStatus() const;

	


	
};
