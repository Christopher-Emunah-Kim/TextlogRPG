#pragma once
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
    unordered_map<string, int32> merchantSellingItemMap; //item, price

public:
    void AddItemForSale(const string& itemName, int32 price);
    void SellItem(Player* player, const string& itemName);
    void BuyItem(Player* player, const string& itemName);

	list<Item*> GetSellableItems(const Player& player);

    virtual void Interact(Player* player) override;
};