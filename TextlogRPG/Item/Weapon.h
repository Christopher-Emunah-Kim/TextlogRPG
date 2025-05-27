#pragma once
#include "Item.h"

class Weapon : public Item
{
private:


public:
	//Default Constructor from Item class
	Weapon(const string& name, int16_t attack, int16_t defense, int16_t agility, EItemType type, int32_t cost)
		: Item("Default Weapon", 10, 0, 0, EItemType::WEAPON, 10) 
	{	}

	//overrided functions
	virtual void getItemInfo() const override;
	virtual void Use(Player* player) override;


	//Destructor
	~Weapon() { cout << "Weapon Destructed"; }
};

