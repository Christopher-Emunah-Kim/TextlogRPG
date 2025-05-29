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
	void ShowItemInfo() const override;
	void Use(Player* player) override;

	//Destructor
	~MiscItem() { cout << "Misc Destructed"; }
};

