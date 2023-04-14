// RealGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager& mainGame = GameManager::getInstance();

    mainGame.realGame();
}