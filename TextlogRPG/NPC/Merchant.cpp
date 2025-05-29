#include "Merchant.h"

void Merchant::AddItemForSale(Item* item, int32_t price) {
    //items.push_back(item);
    itemLists[item] = price;
}

void Merchant::SellItem(Player* player, Item* item) 
{
    map<Item*, int32_t>::iterator it = itemLists.find(item);

    if (it != itemLists.end() && player->GetPlayerData().playerGold >= it->second) 
	{
        player->UseGold(it->second);
        player->EquipItem(item);

		cout << "\n===========================================\n" << endl;
		cout << "[System] " << item->GetItemInfo().itemName << "을(를) 구매했습니다\n" << endl;
		cout << "===========================================\n" << endl;
        
    } else 
	{
		cout << "\n===========================================\n" << endl;
        cout << "[System] 골드가 부족하거나 판매하지 않는 아이템입니다.\n" << endl;
		cout << "===========================================\n" << endl;
    }
}

void Merchant::BuyItem(Player* player, Item* item) 
{
    int32_t price = item->GetItemInfo().itemCost / 2; 
    player->EarnGold(price);
    player->LoseItem(item);

	cout << "\n===========================================\n" << endl;
    cout << "[System] " << item->GetItemInfo().itemName << "을(를) " << price << "골드에 판매했습니다\n" << endl;
	cout << "===========================================\n" << endl;
}

void Merchant::Interact(Player* player) 
{
	cout << "\n===========================================\n" << endl;
    cout << "[System] 상인 " << npcInfo.npcName << "을 만났습니다." << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "[System] 상인을 만나 아이템을 구매합니다.\n" << endl;
	cout << "===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n" << endl;
	cout << "자네인가? 요즘 호구라 불리는 그 " << player->GetName() << "라는 용사가?\n" << endl;
	cout << "크흠흠.. 아니 됐네. 그래서 내게 뭘 원하나?\n" << endl;
	cout << "1. 무기를 구매한다.\n2. 방어구를 구매한다..\n3. 잡템을 판매한다.\n4. 마을로 돌아간다." << endl;
	cout << "\n===========================================\n" << endl;
	char merchantChoice;
	cin >> merchantChoice;
	cin.ignore(1024, '\n');
	system("cls");
	Sleep(1000);
	//TODO : 아이템 구매/판매 로직 구현
	//TODO : 아이템 레이블 정보 불러오기 구현
	int32_t itemPrice = 100;
	string itemName = "UNKNOWN";

	switch (merchantChoice) {
	case '1':
		//무기 구매
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << itemName << "을 " << itemPrice << " 골드에 구매했습니다.\n";
		cout << "===========================================\n" << endl;

		player->UseGold(itemPrice);
		//player->EquipItem(new Weapon);
		Sleep(2000);
		system("cls");
		break;
	case '2':
		//방어구 구매
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << itemName << "을 " << itemPrice << " 골드에 구매했습니다.\n";
		cout << "===========================================\n" << endl;
		player->UseGold(itemPrice);
		// player->EquipItem(new Armor);
		Sleep(2000);
		system("cls");
		break;
	case '3':
		//잡템 판매
		cout << "\n===========================================\n" << endl;
		cout << "[System] " << itemName << "을 " << itemPrice << " 골드에 판매했습니다.\n";
		cout << "===========================================\n" << endl;
		player->EarnGold(5);
		//player -> LoseItem(new MiscItem);
		Sleep(2000);
		system("cls");
		break;
	case '4':
		//마을로 돌아가기
		cout << "\n===========================================\n" << endl;
		cout << "[System] 상점을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		break;
	default:
		cout << "\n===========================================\n" << endl;
		cout << "[System] 잘못된 선택입니다. 상점을 떠나 길거리로 나갑니다.\n" << endl;
		cout << "===========================================\n" << endl;
		break;
	}
}