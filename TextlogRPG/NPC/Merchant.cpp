#include "Merchant.h"
#include "../Item/Item.h"
#include "../Core/ItemManager.h"
#include "../Character/Player.h"

void Merchant::AddItemForSale(const string& itemName, int32 price)
{
    merchantSellingItemMap[itemName] = price;
}

void Merchant::SellItem(Player* player, const string& itemName)
{
	unordered_map<string, int32>::iterator it = merchantSellingItemMap.find(itemName);
	if (it == merchantSellingItemMap.end())
	{
		Common::PrintErrorMsg("판매하지 않는 아이템입니다. 아이템 이름을 확인하세요.");
		Common::PauseAndClearScreen();
		return;
	}

	int32 itemPrice = it->second;

	if (player->GetPlayerData().playerGold < itemPrice)
	{
		Common::PrintErrorMsg("골드가 부족합니다. 아이템을 구매할 수 없습니다.");
		Common::PauseAndClearScreen();
		return;
	}

	Item* item = ItemManager::GetInstance().CreateItem(itemName);

	if (item == nullptr)
	{
		Common::PrintErrorMsg("아이템 생성에 실패했습니다. 아이템 이름을 확인하세요.");
		Common::PauseAndClearScreen();
		return;
	}

	player->UseGold(itemPrice);
	string strEquipItemMsg = item->GetItemInfo().itemName + "을(를) " + to_string(itemPrice) + " 골드에 구매했습니다.";
	Common::PrintSystemMsg(strEquipItemMsg);
	Common::PauseAndClearScreen();

	player->EquipItem(item); 
	//player->AddToInventory(item); 

	Interact(player);

}

void Merchant::BuyItem(Player* player, const string& itemName)
{
	//find item in player's inventory
	list<Item*> sellableItems = GetSellableItems(*player);

	Item* sellItem = nullptr;

	for (list<Item*>::iterator it = sellableItems.begin(); it != sellableItems.end(); ++it)
	{
		Item* item = *it;
		if (item->GetItemInfo().itemName == itemName)
		{
			sellItem = item;
			break;
		}
	}

	/*vector<Item*> miscItems = player->GetInventoryItems(EItemType::MISC);
	Item* sellItem = nullptr;
	for (size_t i = 0; i<miscItems.size(); ++i)
	{
		Item* item = miscItems[i];
		if (item->GetItemInfo().itemName == itemName)
		{
			sellItem = item;
			break;
		}
	}*/

	if (sellItem == nullptr)
	{
		Common::PrintSystemMsg("판매할 아이템을 찾을 수 없습니다. 아이템 이름을 확인하세요.");
		Common::PauseAndClearScreen();
		return;
	}

	int32 sellPrice = sellItem->GetItemInfo().itemCost / 2; // sell price is half of the original cost

	if (sellPrice <= 0)
	{
		Common::PrintSystemMsg("판매할 수 없는 아이템입니다. 아이템 가격이 0 이하입니다.");
		Common::PauseAndClearScreen();
		return;
	}

	player->EarnGold(sellPrice); // Add gold to player's inventory
	player->LoseItem(sellItem); // Remove item from player's inventory
	
	string strSellItemMsg = "[System] " + sellItem->GetItemInfo().itemName + "을(를) 판매합니다. \n판매 가격: " + to_string(sellPrice) + " 골드";
	Common::PrintSystemMsg(strSellItemMsg);
	Common::PauseAndClearScreen();

	Interact(player);
}

list<Item*> Merchant::GetSellableItems(const Player& player) const
{
	list<Item*> sellableItems;

	list<Item*> inventoryWeapons = player.GetInventoryItems(EItemType::WEAPON);
	list<Item*> inventoryArmors = player.GetInventoryItems(EItemType::ARMOR);
	list<Item*> inventoryMiscItems = player.GetInventoryItems(EItemType::MISC);

	Item* equippedWeapon = player.GetEquipmentManager().GetWeapon();
	Item* equippedArmor = player.GetEquipmentManager().GetArmor();
	Item* ownedMisc = player.GetEquipmentManager().GetMisc();

	list<Item*> result;


	for (list<Item*>::const_iterator it = inventoryWeapons.begin(); it != inventoryWeapons.end(); ++it)
	{
		Item* item = *it;
		if (item != equippedWeapon)
		{
			sellableItems.push_back(item);
		}
	}
	for (list<Item*>::const_iterator it = inventoryArmors.begin(); it != inventoryArmors.end(); ++it)
	{
		Item* item = *it;
		if (item != equippedArmor)
		{
			sellableItems.push_back(item);
		}
	}
	for (list<Item*>::const_iterator it = inventoryMiscItems.begin(); it != inventoryMiscItems.end(); ++it)
	{
		Item* item = *it;
		{
			if (item != ownedMisc)
			{
				sellableItems.push_back(item);
			}
		}
	}

	return sellableItems;
}



void Merchant::Interact(Player* player) 
{
	if (player == nullptr)
	{
		Common::PrintErrorMsg("플레이어 정보가 없습니다. 상호작용을 종료합니다.");
		return;
	}

	string strEnterShopMsg = "상점에 들어갑니다. \n" + npcInfo.npcName + "을(를) 만났습니다.";
	Common::PrintSystemMsg(strEnterShopMsg);
	Common::PauseAndClearScreen();

	string strMerchantMsg = "자네인가? 요즘 호구라 불리는 그 " + player->GetName() + "라는 용사가?\n"
		+ "\n크흠흠.. 아니 됐네. 그래서 내게 뭘 원하나?\n" 
		+"\n\n1. 무기를 구매한다.\n\n2. 방어구를 구매한다.\n\n3. 인벤토리의 아이템들을 판매한다.\n\n4. 마을로 돌아간다.\n" ;
	Common::PrintSystemMsg(strMerchantMsg);

	char merchantChoice;
	cin >> merchantChoice;
	cin.ignore(1024, '\n');
	Common::PauseAndClearScreen(1000);


	vector<string> availableWeapons;
	vector<string> availableArmors;
	vector<string> miscItems;
	size_t weaponChoice;
	size_t armorChoice;

	switch (merchantChoice) 
	{
		case '1':
		{
			//Selling Weapons
			for (unordered_map<string, int32>::iterator it = merchantSellingItemMap.begin(); it != merchantSellingItemMap.end(); ++it)
			{
				const pair<string, int32>& pair = *it;
				Item* item = ItemManager::GetInstance().GetItem(pair.first);
				if (item && item->GetItemInfo().itemType == EItemType::WEAPON)
				{
					availableWeapons.push_back(pair.first);
				}
			}
			if (availableWeapons.empty())
			{
				Common::PrintSystemMsg("현재 판매 중인 무기가 없습니다.");
				Common::PauseAndClearScreen();
				break;
			}

			Common::PrintLine();
			cout << "\n[System] 판매 중인 무기 목록\n\n";

			for (size_t i = 0; i < availableWeapons.size(); ++i)
			{
				Item* item = ItemManager::GetInstance().GetItem(availableWeapons[i]);
				if (item) {
					cout << (i + 1) << ". ";
					item->ShowItemInfo();
					cout << "-> 가격: " << merchantSellingItemMap[availableWeapons[i]] << " 골드\n\n";
				}
			}
			cout << (availableWeapons.size() + 1) << ". 뒤로 가기\n";
			Common::PrintLine();

			cin >> weaponChoice;
			cin.ignore(1024, '\n');
			if (weaponChoice > 0 && weaponChoice <= availableWeapons.size())
			{
				SellItem(player, availableWeapons[weaponChoice - 1]);
			}
			else if (weaponChoice == (availableWeapons.size() + 1))
			{
				Common::PauseAndClearScreen();
				Merchant::Interact(player);
			}
		}
			break;
		case '2':
		{
			//Selling Armors
			for (unordered_map<string, int32>::iterator it = merchantSellingItemMap.begin(); it != merchantSellingItemMap.end(); ++it)
			{
				Item* item = ItemManager::GetInstance().GetItem(it->first);
				if (item && item->GetItemInfo().itemType == EItemType::ARMOR)
				{
					availableArmors.push_back(it->first);
				}
			}
			if (availableArmors.empty())
			{
				Common::PrintSystemMsg("현재 판매 중인 방어구가 없습니다.");
				Common::PauseAndClearScreen();
				break;
			}

			Common::PrintLine();
			cout << "\n[System] 판매 중인 방어구 목록\n\n";

			for (size_t i = 0; i < availableArmors.size(); ++i)
			{
				Item* item = ItemManager::GetInstance().GetItem(availableArmors[i]);
				if (item) {
					cout << (i + 1) << ". ";
					item->ShowItemInfo();
					cout << "-> 가격: " << merchantSellingItemMap[availableArmors[i]] << " 골드\n\n";
				}
			}
			cout << (availableArmors.size() + 1) << ". 뒤로 가기\n";
			Common::PrintLine();

			cin >> armorChoice;
			cin.ignore(1024, '\n');
			if (armorChoice > 0 && armorChoice <= availableArmors.size())
			{
				SellItem(player, availableArmors[armorChoice - 1]);
			}
			else if (armorChoice == (availableArmors.size() + 1))
			{
				Merchant::Interact(player);
			}
			Common::PauseAndClearScreen();

		}
			break;
		case '3':
		{
			
			list<Item*> sellableItems = GetSellableItems(*player);
			if (sellableItems.empty())
			{
				Common::PrintSystemMsg("판매할 아이템이 없습니다. 던전에서 몬스터를 처치하고 오세요");
				Common::PauseAndClearScreen();
				Merchant::Interact(player);
				break;
			}

			Common::PrintLine();
			
			size_t index = 0;
			for (list<Item*>::const_iterator it = sellableItems.begin(); it != sellableItems.end(); ++it)
			{
				Item* item = *it;
				cout << (++index) << ". ";
				item->ShowItemInfo();
				int32 sellPrice = item->GetItemInfo().itemCost / 2;
				cout << " -> 판매 가격: " << sellPrice << " 골드\n\n";
			}
			cout << (sellableItems.size() + 1) << ". 뒤로 가기\n";

			Common::PrintLine();

			
			char sellChoice;
			cin >> sellChoice;
			cin.ignore(1024, '\n');

			size_t sellChoiceCount = sellableItems.size();
			if (sellChoice >= '1' && sellChoice <= '0'+sellChoiceCount)
			{
				size_t idx = sellChoice - '1';
				//해당 idx에 해당하는 list 내의 아이템 이름 가져오기.
				//string itemName = sellableItems[idx]->GetItemInfo().itemName;
				list<Item*>::iterator it = sellableItems.begin();
				advance(it, idx);
				string itemName = (*it)->GetItemInfo().itemName;

				BuyItem(player, itemName);
			}
			else if (sellChoice == '0'+sellChoiceCount + 1)
			{
				Merchant::Interact(player);
			}
			else
			{
				Common::PrintSystemMsg("잘못된 입력입니다.");
				Common::PauseAndClearScreen(500);
				Merchant::Interact(player);
			}

			Common::PauseAndClearScreen();

		}
			break;
		case '4':
		{
		//마을로 돌아가기
		Common::PrintSystemMsg("상점을 떠나 길거리로 나갑니다.");
		Common::PauseAndClearScreen();
		}
			break;

		default:
		{
		Common::PrintErrorMsg("잘못된 선택입니다. 상점을 떠나 길거리로 나갑니다..");
		Common::PauseAndClearScreen();
		}
			break;
	}
}