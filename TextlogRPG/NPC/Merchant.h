//#pragma once
//#include "NonPlayerCharacter.h"
//
//class Merchant : public NonPlayerCharacter {
//private:
//    vector<Item*> itemsForSale;
//    map<Item*, int32_t> itemPrices;
//
//public:
//    explicit Merchant(const string& name)
//        : NonPlayerCharacter(name, NPCType::MERCHANT) {}
//
//    void AddItemForSale(Item* item, int32_t price);
//    void SellItem(Player* player, Item* item);
//    void BuyItem(Player* player, Item* item);
//
//    // NPC 상호작용 구현
//    void Interact(Player* player) override;
//};