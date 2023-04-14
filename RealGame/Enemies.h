#pragma once
#include <iostream>

class Enemy {
protected:
    int maxHealth = 10;
    int currentHealth = maxHealth;
    int attack = 1;
    int hitPercent = 0;

    std::string name = "DefaultEnemy";

public:
    int getHealth() { return currentHealth; }
    int getAttack() { return attack; }
    int getHitPercent() { return hitPercent; }

    Enemy(){}

    void takeDamage(int damage) {
        currentHealth -= damage;
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