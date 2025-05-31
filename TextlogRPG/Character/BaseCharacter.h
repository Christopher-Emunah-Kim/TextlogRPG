#pragma once
#include "../Util/Common.h"
#include "CharacterStatus.h"

using namespace std;

struct FCharacterInfo
{
	CharacterStatus characterStats;
	int32_t maxHealth = 100;
	int32_t health = 100;
	int16_t level = 1;
	string characterName = "UNKNOWN";

};

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
