#pragma once
#include "Item.h"

class Armor : public Item
{
private:

public:
	//Default Constructor from Item class
	Armor()
		: Item()
	{	}

	//overrided function
	Armor* CloneItem() const override
	{
		return new Armor(*this);
	}
	void EquippedBy(Player* player) override;

	//Destructor
	~Armor() { }
};

