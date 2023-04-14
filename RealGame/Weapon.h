#pragma once
#include <iostream>

class Weapon {
public:
    int damage = 0;
    std::string  weaponName = "";

    // Default constructor
    Weapon() {
        damage = 3;
        weaponName = "Epee";
    }

    // Constructor overloading
    Weapon(int damage, std::string name) {
        this->damage = damage;
        this->weaponName = name;
    }

    /// <summary>
    /// Change weapon characteristics : overload 1
    /// </summary>
    /// <param name="newArme">new Arme reference</param>
    void change(Weapon& newArme) {
        this->damage = newArme.damage;
        this->damage = newArme.damage;
    }

    /// <summary>
    /// Change weapon characteristics : overload 2
    /// </summary>
    /// <param name="newDegats">new damage</param>
    /// <param name="newNomArme">new name</param>
    void change(int newDegats, std::string newNomArme) {
        this->damage = newDegats;
        this->weaponName = newNomArme;
    }

};