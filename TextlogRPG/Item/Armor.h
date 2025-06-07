#pragma once
#include "Item.h"

class Armor : public Item
{
public:
	//Default Constructor from Item class
	Armor()
		: Item()
	{	}
	//Destructor
	~Armor() {}

public:

	//overrided function
	Armor* CloneItem() const override
	{
		return new Armor(*this);
	}
	void EquippedBy(Player* player) override;

	
};

