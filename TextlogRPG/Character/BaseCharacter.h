#pragma once
#include "../Character/CharacterInfo.h"

using namespace std;



class BaseCharacter abstract
{
protected:
	FCharacterInfo characterInfo;

public:
	
    //Default Constructor
	explicit BaseCharacter()
    : characterInfo{ FCharacterInfo{} } { }

	//User-Defined Constructor
	explicit BaseCharacter(const FCharacterInfo& info) : characterInfo(info) {}

	//virtual destructor
	virtual ~BaseCharacter() = default;

	virtual FCharacterInfo GetCharacterInfo() const { return characterInfo; }

	//Pure virtual functions
	virtual void TakeDamage(BaseCharacter& target) = 0;
	virtual void Attack(BaseCharacter* target) = 0;

	BaseCharacter(const BaseCharacter&) = default;
	BaseCharacter& operator =(const BaseCharacter&) = default;
	BaseCharacter(BaseCharacter&&) = default;
	BaseCharacter& operator =(BaseCharacter&&) = default;
};
