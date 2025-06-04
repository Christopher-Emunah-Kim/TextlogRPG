#pragma once
#include "NonPlayerCharacter.h"

class Healer : public NonPlayerCharacter {
private:
    int32 healCost;

public:
	explicit Healer(const string& name, int32 cost)
		: NonPlayerCharacter(), healCost(cost) { SetName(name);	}

    int32 GetHealCost() const { return healCost; }

    void HealPlayer(Player* player, int32 cost);

    // Interact with Player
    void Interact(Player* player) override;
};