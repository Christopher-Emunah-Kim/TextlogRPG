#pragma once
#include "Item.h"


class MiscItem : public Item
{
private:

public:
	//Default Constructor from Item class
	MiscItem(const string& name, int16_t attack, int16_t defense, int16_t agility, EItemType type, int32_t cost)
		:Item("Default Misc", 0, 0, 0, EItemType::MISC, 1)
	{ }

	//overrided functions
	virtual void getItemInfo() const override;
	virtual void Use(Player* player) override;

	//Destructor
	~MiscItem() { cout << "Misc Destructed"; }
};

