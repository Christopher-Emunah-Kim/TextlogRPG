#pragma once
#include "Item.h"


class MiscItem : public Item
{
public:
	//Default Constructor from Item class
	MiscItem()
		:Item()
	{ }
	//Destructor
	~MiscItem() {}

public:
	//overrided functions
	virtual MiscItem*	CloneItem() const override
	{
		return new MiscItem(*this);
	}

	virtual void		EquippedBy(Player* player) override;

	
};

