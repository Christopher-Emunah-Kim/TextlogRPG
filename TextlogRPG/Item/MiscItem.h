﻿#pragma once
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
	MiscItem* CloneItem() const override
	{
		return new MiscItem(*this);
	}

	void EquippedBy(Player* player) override;

	
};

