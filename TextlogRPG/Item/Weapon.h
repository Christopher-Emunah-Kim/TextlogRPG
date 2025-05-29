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
	virtual void ShowItemInfo() const override;
	virtual void Use(Player* player) override;


	//Destructor
	~Weapon() { cout << "Weapon Destructed"; }
};

