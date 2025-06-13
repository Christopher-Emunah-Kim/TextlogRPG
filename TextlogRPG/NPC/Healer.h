#pragma once
#include "NonPlayerCharacter.h"

class Healer : public NonPlayerCharacter 
{
public:
	explicit Healer(const string& name, int32 cost)
		: NonPlayerCharacter(), healCost(cost) 
	{
		SetName(name);
	}

private:
    int32	healCost;

public:
	
    int32			GetHealCost() const { return healCost; }

    void			HealPlayer(Player* player, int32 cost);

    // Interact with Player
	virtual void	Interact(Player* player) override;
};