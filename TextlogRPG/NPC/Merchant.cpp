#include "Merchant.h"

void Merchant::AddItemForSale(Item* item, int32_t price) {
    itemsForSale.push_back(item);
    itemPrices[item] = price;
}

void Merchant::SellItem(Player* player, Item* item) {
    auto it = itemPrices.find(item);
    if (it != itemPrices.end() && player->GetPlayerData().playerGold >= it->second) {
        player->UseGold(it->second);
        player->EquipItem(item);
        cout << "[System] " << item->getItemName() << "을(를) 구매했습니다." << endl;
    } else {
        cout << "[System] 골드가 부족하거나 판매하지 않는 아이템입니다." << endl;
    }
}

void Merchant::BuyItem(Player* player, Item* item) {
    int32_t price = item->getItemCost() / 2; // 예시: 판매가는 원가의 50%
    player->EarnGold(price);
    player->LoseItem(item);
    cout << "[System] " << item->getItemName() << "을(를) " << price << "골드에 판매했습니다." << endl;
}

void Merchant::Interact(Player* player) {
    cout << "[System] 상인 " << npcName << "와 상호작용합니다." << endl;
    // 실제 게임에서는 메뉴를 띄워서 SellItem/BuyItem 호출
}