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
	virtual void ShowItemInfo() const override;
	virtual void Use(Player* player) override;

	//Destructor
	~Armor() { cout << "Armor Destructed"; }
};

