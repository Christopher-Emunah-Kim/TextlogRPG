#pragma once
#include "Item.h"


class MiscItem : public Item
{
private:

public:
	//Default Constructor from Item class
	MiscItem()
		:Item()
	{ }

	//overrided functions
	virtual void ShowItemInfo() const override;
	virtual void Use(Player* player) override;

	//Destructor
	~MiscItem() { cout << "Misc Destructed"; }
};

