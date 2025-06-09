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
	virtual Armor* CloneItem() const override
	{
		return new Armor(*this);
	}
	virtual void EquippedBy(Player* player) override;

	
};

