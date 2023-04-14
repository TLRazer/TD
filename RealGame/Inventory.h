#pragma once
#include <list>
#include <iostream>

class Inventory {
public:
	int bomb = 0;
	int key = 0;
	int gold = 0;

	int maxBomb = 5;
	int maxKey = 5;
	int maxGold = 30;

	std::list<std::string> uniqueItems;

	Inventory() {
		bomb = 0;
		key = 0;
		gold = 0;
	}

	Inventory(int bombs, int keys, int golds) {
		bomb = bombs;
		key = keys;
		gold = golds;
	}

	Inventory(int bombs, int keys, int golds, std::list<std::string> itemList) {
		bomb = bombs;
		key = keys;
		gold = golds;
		uniqueItems = itemList;
	}

	void addBombs(int number) { bomb += number; if (bomb > maxBomb) bomb = maxBomb; }
	void addKeys(int number) { key += number; if (key > maxKey) key = maxKey; }
	void addGold(int number) { gold += number; if (gold > maxGold) gold = maxGold; }

	void removeBombs(int number) { bomb -= number; if (bomb < 0) bomb = 0; }
	void removeKeys(int number) { key -= number; if (key > 0) key = 0; }
	void removeGold(int number) { gold -= number; if (gold > 0) gold = 0; }

	void addItem(std::string newItem) { uniqueItems.push_back(newItem); }
	void removeItem(std::string itemToRemove) { uniqueItems.remove(itemToRemove); }
	void clearItems() { uniqueItems.clear(); }

	void shuffleInventory() {
		int temp = bomb + key + gold;

		int temp2 = rand() % (temp + 1);
		gold = temp2;
		temp = temp - temp2;

		temp2 = rand() % (temp + 1);
		bomb = temp2;
		key = temp - temp2;

	}

	void clearInventory() {
		bomb = 0;
		key = 0;
		gold = 0;
		clearItems();
	}
};