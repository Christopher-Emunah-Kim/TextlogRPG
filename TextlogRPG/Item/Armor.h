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
	void ShowItemInfo() const override;
	void Use(Player* player) override;

	//Destructor
	~Armor() { }
};

