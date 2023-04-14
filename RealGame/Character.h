#pragma once
#include <iostream>
#include <list>
#include "Weapon.h"
#include "Inventory.h"

class Character {
protected:
    int maxHealth = 0;
    int currentHealth = 0;

    int maxMana = 0;
    int currentMana = 0;

    Weapon* myWeapon;
    Inventory* myInventory;
    // std::list<std::string> myInventory;

    std::string characterName = "";
    std::string job = "Thief";

    /*** CONSTRUCTORS ***/
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;
    // Default constructor
    Character() {
        characterName = "Traveler";
        job = "Thief";
        maxHealth = 15 + rand() % 4;
        maxMana = 3;

        myWeapon = new Weapon();
        myInventory = new Inventory();

        currentHealth = maxHealth;
        currentMana = maxMana;
    }

    // Constructor overload 1 : All variables as parameters
    Character(std::string nom, int vie, int mana, int degats, std::string nomArme) {
        this->characterName = nom;
        this->maxHealth = vie;
        this->maxMana = mana;

        this->myWeapon = new Weapon(degats, nomArme);

        currentHealth = maxHealth;
        currentMana = maxMana;
        myInventory = new Inventory();
    }

    // Constructor overload 2 : Character parameter
    Character(Character& persoACopier) {
        this->maxHealth = persoACopier.getMaxHealth();
        this->maxMana = persoACopier.getMaxMana();
        this->characterName = persoACopier.getName();

        this->myWeapon = persoACopier.getWeapon();

        currentHealth = maxHealth;
        currentMana = maxMana;
        myInventory = new Inventory();
    }
public:
    // Singleton
    static Character& getInstance() {
        static Character INSTANCE;
        return INSTANCE;
    }

/*** GETTERS/SETTERS ***/
    //Health
    int getMaxHealth() { return maxHealth; }
    void setMaxHealth(int newValue) { maxHealth = newValue; }
    int getCurrentHealth() { return currentHealth; }

    //Mana
    int getMaxMana() { return maxMana; }
    void setMaxMana(int newValue) { maxMana = newValue; }
    int getCurrentMana() { return currentMana; }

    //Name and job
    std::string getName() { return characterName; }
    void setName(std::string name) { characterName = name; }
    std::string getJob() { return job; }
    void setJob(std::string newJob){
        if (newJob == "Barbarian") {
            job = "Barbarian";
            maxHealth = std::floor(maxHealth * 1.3);
            currentHealth = maxHealth;

            maxMana = 0;
            currentMana = 0;

            myWeapon->change(3, "Wooden Club");
            myInventory->addBombs(2 + rand()%2);
            myInventory->addItem("Torch");
        }
        else if (newJob == "Arcanist") {
            job = "Arcanist";

            maxMana = std::floor(maxMana * 3);
            currentMana = maxMana;

            myWeapon->change(1, "Fork");
            myInventory->addGold(rand() % 6);
            myInventory->addItem("Electric Catalyst");
        }
        else {
            job = "Thief";

            myWeapon->change(3, "Daggers");
            myInventory->addBombs(2);
            myInventory->addGold(5 + rand() % 11);
            myInventory->addKeys(2);
            myInventory->addItem("Somebody's Empty Purse");
        }
    }

    //Items
    Weapon* getWeapon() { return myWeapon; }
    Inventory* getInventory() { return myInventory; }
    int getBombs() { return myInventory->bomb; }
    int getKeys() { return myInventory->key; }
    int getGold() { return myInventory->gold; }




/*** FUNCTIONS ***/
    void characChecking() {
        std::cout << "\n|-------- " << characterName << " --------|"
            << "\n|\n| Job : " << job
            << "\n|\n| Health : " << currentHealth << "/" << maxHealth
            << "\n| Mana : " << currentMana << "/" << maxMana
            << "\n| Weapon : " << myWeapon->weaponName << " (" << myWeapon->damage << "dmg)"
            << "\n|\n| Bombs ~ " << getBombs()
            << "\n| Keys ~ " << getKeys()
            << "\n| Gold ~ " << getGold()
            << "\n|-------------------------------------------------------";
    }

    /// <summary>
    /// Receive damage and checks if character is dead
    /// </summary>
    /// <param name="nombreDegats">number of damage received</param>
    void takeDamage(int nombreDegats) {
        this->currentHealth -= nombreDegats;

        if (!isAlive()) {
            std::cout << "|-- Character '" << this->currentHealth << "' died --|\n";
            this->currentHealth = 0;
        }
    }

    /// <summary>
    /// Checks if the character is dead
    /// </summary>
    /// <returns>is he dead?</returns>
    bool isAlive() {
        if (currentHealth <= 0) {
            return false;
        }
        else {
            return true;
        }
    }

    /// <summary>
    /// Attacks another Character with current attack power
    /// </summary>
    /// <param name="persoAAttaquer">Reference to the other Personnage</param>
    void attack(Character& target){
        std::cout << this->characterName + " strikes " << target.getName() << " for " << this->myWeapon->damage <<
            " damage with their " << this->myWeapon->weaponName << "!\n";
        target.takeDamage(this->myWeapon->damage);
    }

    /// <summary>
    /// Change current weapon's damage and name
    /// </summary>
    /// <param name="degatsArme">new damage</param>
    /// <param name="nomArme">new name</param>
    void changeWeapon(int degatsArme, std::string nomArme) {
        this->myWeapon->change(degatsArme, nomArme);
    }

    

};
