#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon()
		: Item() 	{	}
	~Weapon() {}


public:
	//overrided functions
	Weapon* CloneItem() const override
	{
		return new Weapon(*this);
	}
	void EquippedBy(Player* player) override;


	
};

