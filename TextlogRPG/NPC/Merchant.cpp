#include "Merchant.h"
#include "../Item/Item.h"
#include "../Item/ItemManager.h"

void Merchant::AddItemForSale(const string& itemName, int32_t price)
{
    itemLists[itemName] = price;
}

void Merchant::SellItem(Player* player, const string& itemName)
{
	map<string, int32_t>::iterator it = itemLists.find(itemName);
	if (it == itemLists.end())
	{
		cout << "\n===========================================\n";
		cout << "\n[Error] 판매하지 않는 아이템입니다.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		return;
	}

	int32_t itemPrice = it->second;
	if (player->GetPlayerData().playerGold < itemPrice)
	{
		cout << "\n===========================================\n";
		cout << "\n[System] 골드가 부족합니다. 아이템을 구매할 수 없습니다.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		return;
	}

	Item* item = ItemManager::GetInstance().CreateItem(itemName);
	if (item == nullptr)
	{
		cout << "\n===========================================\n";
		cout << "\n[Error] 아이템을 생성할 수 없습니다. 아이템 이름을 확인하세요.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		return;
	}

	player->UseGold(itemPrice);
	player->EquipItem(item); 
	player->AddToInventory(item); 
	cout << "\n===========================================\n";
	cout << "\n[System] " << item->GetItemInfo().itemName << "을(를) " << itemPrice << " 골드에 구매했습니다.\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	
}

void Merchant::BuyItem(Player* player, const string& itemName)
{
	//find item in player's inventory
	vector<Item*> miscItems = player->GetInventoryItems(EItemType::MISC);
	Item* sellItem = nullptr;
	for (Item* item : miscItems)
	{
		if (item->GetItemInfo().itemName == itemName)
		{
			sellItem = item;
			break;
		}
	}
	if (sellItem == nullptr)
	{
		cout << "\n===========================================\n";
		cout << "\n[Error] 판매할 아이템이 없습니다. 아이템 이름을 확인하세요.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		return;
	}
	int32_t sellPrice = sellItem->GetItemInfo().itemCost / 2; // sell price is half of the original cost

	if (sellPrice <= 0)
	{
		cout << "\n===========================================\n";
		cout << "\n[Error] 판매할 수 없는 아이템입니다. 아이템 가격이 0 이하입니다.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
		return;
	}

	player->EarnGold(sellPrice); // Add gold to player's inventory
	player->LoseItem(sellItem); // Remove item from player's inventory
	cout << "\n===========================================\n";
	cout << "\n[System] " << sellItem->GetItemInfo().itemName << "을(를) " << sellPrice << " 골드에 판매했습니다.\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");

}

void Merchant::Interact(Player* player) 
{
	cout << "\n===========================================\n";
    cout << "\n[System] 상점에 들어갑니다.\n\n상인 " << npcInfo.npcName << "을(를) 만났습니다.\n";
	cout << "\n===========================================\n" << endl;
	Sleep(2000);
	system("cls");
	cout << "\n===========================================\n";
	cout << "\n자네인가? 요즘 호구라 불리는 그 " << player->GetName() << "라는 용사가?\n";
	cout << "\n크흠흠.. 아니 됐네. 그래서 내게 뭘 원하나?\n";
	cout << "\n\n1. 무기를 구매한다.\n\n2. 방어구를 구매한다.\n\n3. 잡템을 판매한다.\n\n4. 마을로 돌아간다.\n";
	cout << "\n===========================================\n" << endl;
	char merchantChoice;
	cin >> merchantChoice;
	cin.ignore(1024, '\n');
	system("cls");
	Sleep(1000);

	//TODO : 아이템 레이블 정보 불러오기 구현

	vector<string> availableWeapons;
	vector<string> availableArmors;
	vector<string> miscItems;
	int weaponChoice;
	int armorChoice;

	switch (merchantChoice) 
	{
	case '1':
	{
		//Selling Weapons
		for (const pair<string, int32_t>& pair : itemLists)
		{
			Item* item = ItemManager::GetInstance().GetItem(pair.first);
			if (item && item->GetItemInfo().itemType == EItemType::WEAPON)
			{
				availableWeapons.push_back(pair.first);
			}
		}
		if (availableWeapons.empty())
		{
			cout << "\n===========================================\n";
			cout << "[System] 현재 판매 중인 무기가 없습니다.\n";
			cout << "\n===========================================\n" << endl;
			Sleep(2000);
			system("cls");
			break;
		}

		cout << "\n===========================================\n";
		cout << "\n[System] 판매 중인 무기 목록\n\n";

		for (size_t i = 0; i < availableWeapons.size(); ++i)
		{
			Item* item = ItemManager::GetInstance().GetItem(availableWeapons[i]);
			if (item) {
				cout << (i + 1) << ". ";
				item->ShowItemInfo();
				cout << "-> 가격: " << itemLists[availableWeapons[i]] << " 골드\n\n";
			}
		}
		cout << (availableWeapons.size() + 1) << ". 뒤로 가기\n";
		cout << "\n===========================================\n" << endl;

		cin >> weaponChoice;
		cin.ignore(1024, '\n');
		if (weaponChoice > 0 && weaponChoice <= static_cast<int>(availableWeapons.size()))
		{
			SellItem(player, availableWeapons[weaponChoice - 1]);
		}
		else if (weaponChoice == static_cast<int>(availableWeapons.size() + 1))
		{
			Sleep(2000);
			system("cls");
			Merchant::Interact(player);
		}
		Sleep(2000);
		system("cls");

	}
	break;
	case '2':
	{
		//Selling Armors
		for (const pair<string, int32_t>& pair : itemLists)
		{
			Item* item = ItemManager::GetInstance().GetItem(pair.first);
			if (item && item->GetItemInfo().itemType == EItemType::ARMOR)
			{
				availableArmors.push_back(pair.first);
			}
		}
		if (availableArmors.empty())
		{
			cout << "\n===========================================\n";
			cout << "[System] 현재 판매 중인 방어구가 없습니다.\n";
			cout << "\n===========================================\n" << endl;
			Sleep(2000);
			system("cls");
			break;
		}

		cout << "\n===========================================\n";
		cout << "\n[System] 판매 중인 방어구 목록\n\n";

		for (size_t i = 0; i < availableArmors.size(); ++i)
		{
			Item* item = ItemManager::GetInstance().GetItem(availableArmors[i]);
			if (item) {
				cout << (i + 1) << ". ";
				item->ShowItemInfo();
				cout << "-> 가격: " << itemLists[availableArmors[i]] << " 골드\n\n";
			}
		}
		cout << (availableArmors.size() + 1) << ". 뒤로 가기\n";
		cout << "\n===========================================\n" << endl;

		cin >> armorChoice;
		cin.ignore(1024, '\n');
		if (armorChoice > 0 && armorChoice <= static_cast<int>(availableArmors.size()))
		{
			SellItem(player, availableArmors[armorChoice - 1]);
		}
		else if (armorChoice == static_cast<int>(availableArmors.size() + 1))
		{
			Sleep(2000);
			system("cls");
			Merchant::Interact(player);
		}
		Sleep(2000);
		system("cls");

	}
	break;
	case '3':
	{
		//Buying Misc Items
		vector<Item*> miscItems = player->GetInventoryItems(EItemType::MISC);
		if (miscItems.empty()) {
			cout << "\n===========================================\n";
			cout << "\n[System] 판매할 잡템이 없습니다. 던전에서 몬스터를 처치하고 오세요.\n";
			cout << "\n===========================================\n" << endl;
			Sleep(2000);
			system("cls");
			Merchant::Interact(player);
			break;
		}

		cout << "\n===========================================\n";
		cout << "\n[System] 판매 가능한 잡템 목록:\n\n";
		for (size_t i = 0; i < miscItems.size(); ++i) {
			cout << (i + 1) << ". ";
			miscItems[i]->ShowItemInfo();
			int sellPrice = miscItems[i]->GetItemInfo().itemCost / 2;
			cout << " -> 판매 가격: " << sellPrice << " 골드\n\n";
		}
		cout << (miscItems.size() + 1) << ". 뒤로 가기\n";
		cout << "\n===========================================\n" << endl;

		int miscChoice;
		cin >> miscChoice;
		cin.ignore(1024, '\n');
		if (miscChoice > 0 && miscChoice <= static_cast<int>(miscItems.size()))
		{
			BuyItem(player, miscItems[miscChoice - 1]->GetItemInfo().itemName);
		}
		else if (miscChoice == static_cast<int>(miscItems.size() + 1))
		{
			Sleep(2000);
			system("cls");
			Merchant::Interact(player);
		}
		Sleep(2000);
		system("cls");

	}
	break;
	case '4':
	{
		//마을로 돌아가기
		cout << "\n===========================================\n";
		cout << "\n[System] 상점을 떠나 길거리로 나갑니다.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	break;

	default:
	{
		cout << "\n===========================================\n";
		cout << "[System] 잘못된 선택입니다. 상점을 떠나 길거리로 나갑니다.\n";
		cout << "\n===========================================\n" << endl;
		Sleep(2000);
		system("cls");
	}
	break;
	}
}