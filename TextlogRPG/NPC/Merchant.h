#pragma once
#include "NonPlayerCharacter.h"

class Merchant : public NonPlayerCharacter {
private:
    //vector<Item*> items;
    map<string, int32_t> itemLists; //item, price

public:
    explicit Merchant(const string& name)
		: NonPlayerCharacter() { SetName(name);	}

    void AddItemForSale(const string& itemName, int32_t price);
    void SellItem(Player* player, const string& itemName);
    void BuyItem(Player* player, const string& itemName);

    void Interact(Player* player) override;
};