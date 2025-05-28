#pragma once
#include "../Util/Common.h"
#include "../Item/Item.h"
#include "../Character/Player.h"

using namespace std;

enum class ENpcType 
{
	NONE,
	HEALER, 
	MERCHANT 
};

struct FNpcInfo
{
	ENpcType type = ENpcType::NONE;
	string npcName = "Default NPC";
};

class NonPlayerCharacter abstract 
{
protected:
	FNpcInfo npcInfo;

public:
	explicit NonPlayerCharacter()
		: npcInfo{ FNpcInfo{} } {
	}

    explicit NonPlayerCharacter(const FNpcInfo& info)
        : npcInfo(info) {}

    virtual ~NonPlayerCharacter() = default;

    virtual string GetName() const { return npcInfo.npcName; }
    virtual ENpcType GetType() const { return npcInfo.type; }
    virtual void SetName(const string& name) { npcInfo.npcName = name; }

    // Interaction Func Interface
    virtual void Interact(Player* player) = 0;
};