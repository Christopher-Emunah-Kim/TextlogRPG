#pragma once
#include "NonPlayerCharacter.h"

class Healer : public NonPlayerCharacter {
private:
    uint32 healCost;

public:
	explicit Healer(const string& name, uint32 cost)
		: NonPlayerCharacter(), healCost(cost) { SetName(name);	}

    uint32 GetHealCost() const { return healCost; }

    void HealPlayer(Player* player, uint32 cost);

    // Interact with Player
    void Interact(Player* player) override;
};