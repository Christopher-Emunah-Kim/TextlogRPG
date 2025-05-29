#pragma once
#include "NonPlayerCharacter.h"

class Healer : public NonPlayerCharacter {
private:
    int32_t healCost;

public:
	explicit Healer(const string& name, int32_t cost)
		: NonPlayerCharacter(), healCost(cost) { SetName(name);	}

    int32_t GetHealCost() const { return healCost; }

    void HealPlayer(Player* player, int32_t cost);

    // Interact with Player
    void Interact(Player* player) override;
};