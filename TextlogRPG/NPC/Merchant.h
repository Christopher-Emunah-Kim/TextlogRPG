﻿#pragma once
#include "NonPlayerCharacter.h"

class Merchant : public NonPlayerCharacter 
{
public:
	explicit Merchant(const string& name)
		: NonPlayerCharacter() 
	{
		SetName(name);
	}

private:
    //vector<Item*> items;
    unordered_map<string, int32> itemLists; //item, price

public:
    void AddItemForSale(const string& itemName, int32 price);
    void SellItem(Player* player, const string& itemName);
    void BuyItem(Player* player, const string& itemName);

    void Interact(Player* player) override;
};