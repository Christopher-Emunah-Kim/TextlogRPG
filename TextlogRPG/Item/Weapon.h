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
	virtual Weapon*		CloneItem() const override
	{
		return new Weapon(*this);
	}
	virtual void		EquippedBy(Player* player) override;


	
};

