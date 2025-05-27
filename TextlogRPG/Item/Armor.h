#pragma once
#include "Item.h"

class Armor : public Item
{
private:

public:
	//Default Constructor from Item class
	Armor(const string& name, int16_t attack, int16_t defense, int16_t agility, EItemType type, int32_t cost)
		: Item("Default Amor", 0, 10, 0, EItemType::ARMOR, 10)
	{	}

	//overrided function
	virtual void getItemInfo() const override;
	virtual void Use(Player* player) override;

	//Destructor
	~Armor() { cout << "Armor Destructed"; }
};

