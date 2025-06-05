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

	/*explicit BaseCharacter()
		: characterInfo{ FCharacterInfo{} } {
	}*/

	//User-Defined Constructor
	//explicit BaseCharacter(const FCharacterInfo& info) : characterInfo(info) {}

protected:
	//FCharacterInfo characterInfo;

public:
	
	//virtual const FCharacterInfo& GetCharacterInfo() const { return characterInfo; }
	//virtual FCharacterInfo& GetCharacterInfoRef() { return characterInfo; }

	//Pure virtual functions
	virtual const FCharacterInfo& GetCharacterInfo() const = 0;
	virtual void ReceiveDamageFrom(BaseCharacter& target) = 0;
	virtual void Attack(BaseCharacter* target) = 0;

	BaseCharacter(const BaseCharacter&) = default;
	BaseCharacter& operator =(const BaseCharacter&) = default;
	BaseCharacter(BaseCharacter&&) = default;
	BaseCharacter& operator =(BaseCharacter&&) = default;
};
