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
	MiscItem* CloneItem() const override
	{
		return new MiscItem(*this);
	}
	void ShowItemInfo() const override;
	void Use(Player* player) override;

	//Destructor
	~MiscItem() { }
};

