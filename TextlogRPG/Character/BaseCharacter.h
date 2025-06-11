#pragma once
#include "../Character/CharacterInfo.h"

using namespace std;



class BaseCharacter abstract
{
public:
	//Default Constructor
	explicit BaseCharacter() {	}

	//virtual destructor
	virtual ~BaseCharacter() = default;

	BaseCharacter(const BaseCharacter&) = default;
	BaseCharacter& operator =(const BaseCharacter&) = default;
	BaseCharacter(BaseCharacter&&) = default;
	BaseCharacter& operator =(BaseCharacter&&) = default;

public:
	
	//Pure virtual functions
	virtual const FCharacterInfo& GetCharacterInfo() const = 0;
	virtual void ApplyDamageFrom(BaseCharacter& attacker) = 0;
	virtual void Attack(BaseCharacter* target) = 0;

};
