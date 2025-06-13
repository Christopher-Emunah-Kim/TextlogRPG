#pragma once
#include "../Util/Common.h"
#include "../Item/Item.h"

using namespace std;

class Player;

enum class ENpcType : uint8
{
	NONE,
	HEALER, 
	MERCHANT 
};

struct FNpcInfo
{
	ENpcType	type = ENpcType::NONE;
	string		npcName = "Default NPC";
};


class NonPlayerCharacter abstract 
{
public:
	explicit NonPlayerCharacter()
		: npcInfo{ FNpcInfo{} } {
	}

	explicit NonPlayerCharacter(const FNpcInfo& info)
		: npcInfo(info) {
	}

	virtual ~NonPlayerCharacter() = default;

protected:
	FNpcInfo	npcInfo;

public:
	
    inline virtual string		GetName() const { return npcInfo.npcName; }
    inline virtual ENpcType		GetType() const { return npcInfo.type; }
    inline virtual void			SetName(const string& name) { npcInfo.npcName = name; }

    // Interaction Func Interface
    virtual void				Interact(Player* player) = 0;
};