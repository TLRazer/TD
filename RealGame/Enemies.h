#pragma once
#include <iostream>
#include <list>
#include <string>
#include <time.h>
#include <random>

class Enemy {
protected:
    int maxHealth = 10;
    int currentHealth = maxHealth;
    int attack = 1;
    int hitPercent = 0;

    std::string name = "DefaultEnemy";
    std::string possibleNames[7] =
    { "Blop", "Giant rat", "Living rock",
        "Goblin", "Squirrel-Dragon", "Dirtpicker", "Skeleton" };

public:
    int getHealth() { return currentHealth; }
    int getAttack() { return attack; }
    int getHitPercent() { return hitPercent; }
    std::string getName() { return name; }

    Enemy(){
		int sizeOfNames = end(possibleNames) - begin(possibleNames);
		srand(time(NULL));
		int random1 = rand() % (sizeOfNames);
        name = possibleNames[random1];

        maxHealth = 9 + (rand()%5);
        currentHealth = maxHealth;

        attack = 1 + (rand() % 2);
    }

    void takeDamage(int damage) {
        currentHealth -= damage;
        std::cout << name << " took " << damage << " damage.\n";
        if (currentHealth <= 0) {
            std::cout << name << " died!\n";
        }
    }
};

class Jelly : public Enemy {
public:
    Jelly() {
        maxHealth = 10 + (rand()%4);    // Between 10 and 13 HP
        currentHealth = maxHealth;
        attack = 1;
        hitPercent = 40;                // 40% accuracy
    }

};