#pragma once
#include "Item.h"

class Weapon : public Item
{
private:


public:
	//Default Constructor from Item class
	Weapon()
		: Item() 	{	}

	//overrided functions
	Weapon* CloneItem() const override
	{
		return new Weapon(*this);
	}
	void EquippedBy(Player* player) override;


	//Destructor
	~Weapon() { }
};

