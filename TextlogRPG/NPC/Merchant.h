#pragma once
#include "NonPlayerCharacter.h"

class Merchant : public NonPlayerCharacter {
private:
    //vector<Item*> items;
    map<Item*, int32_t> itemLists; //item, price

public:
	//TODO : vector<Item*> 생성자 구성해서 초기화멤버리스트에 넣기.
    explicit Merchant(const string& name)
		: NonPlayerCharacter() { SetName(name);	}

    void AddItemForSale(Item* item, int32_t price);
    void SellItem(Player* player, Item* item);
    void BuyItem(Player* player, Item* item);

    void Interact(Player* player) override;
};