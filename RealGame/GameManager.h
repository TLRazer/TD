#pragma once
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include "Character.h"
#include "Enemies.h"

class EnemyFacade {
public:
	template<typename enemyType>
	void takeDamage(enemyType& enemyToDamage, int damageAmount) {
		enemyToDamage.takeDamage(damageAmount);
		if constexpr (std::is_same<enemyType, Jelly>::value) {
			std::cout << "You hit a Jelly D:\n";
		}
	}
};

class GameManager {
private:
	int gameCounter = 0;

	int floorLevel = 0;
	int combatCounter = 0;
	int enemiesSlain = 0;
	int treasuresFound = 0;

	std::string dungeonName = "The Cave";

	Character& playerCharacter = Character::getInstance();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager() {}
public:
	// Singleton
	static GameManager& getInstance() {
		static GameManager INSTANCE;
		return INSTANCE;
	}

/*** GETTERS/SETTERS ***/
	int getFloorLevel() { return floorLevel; }
	int getCombatCounter() { return combatCounter; }
	int getEnemiesSlain() { return enemiesSlain; }
	int getTreasuresFound() { return treasuresFound; }

	void resetGame() {
		floorLevel = 0;
		combatCounter = 0;
		enemiesSlain = 0;
		treasuresFound = 0;
	}

	std::string userTextInput(std::string textToDisplay, std::list<std::string> possibleResponses) {
		std::string response = "";
		std::string possibilities = "";
		bool validResponse = false;

		int iterator = 0;
		for (std::string p : possibleResponses) {
			iterator++;
			possibilities += " - " + std::to_string(iterator) + " : " + p + "\n";
		}

		while (!validResponse) {
			std::cout << textToDisplay << "\n" << possibilities;
			std::cin >> response;

			if (std::find(possibleResponses.begin(), possibleResponses.end(), response) != possibleResponses.end()) {
				validResponse = true;
			}
			else {
				std::cout << "\n~ Incorrect response. ~\n";
			}
		}
		return response;
	};

	std::string dungeonNameGenerator() {
		std::string prefix[] =
		{"The Magnificent", "Mr. Rat's", "The Darkest",
			"The Basic", "Magic Lord's", "The Sunken", "The High definition"};

		std::string sufix[] =
		{ "Dungeon", "Cave", "Labyrinth",
			"Magic Closet", "Tower", "Infinite Planes",
			"Castle", "Forest", "Secret Hideout"};

		int sizeOfPrefix = end(prefix) - begin(prefix);
		int sizeOfSufix = end(sufix) - begin(sufix);

		srand(time(NULL));
		int random1 = rand() % (sizeOfPrefix);
		int random2 = rand() % (sizeOfSufix);
		return (prefix[random1]) + " " + (sufix[random2]);
	}

	void classSelection() {
		std::string selection = userTextInput("First, select your starting job :",
			{ "Barbarian","Arcanist","Thief" });
		//playerCharacter->setJob(selection);

		//playerCharacter.characChecking();
		std::cout << "what" ;


		playerCharacter.characChecking();

	}

	void launchGame() {
		dungeonName = dungeonNameGenerator();

		std::cout << "/*-- THE REAL GAME, Attempt : " << gameCounter << ", "<< dungeonName <<" --*/\n\n"
		<< "-------------------------------------------------------------------------------------\n"
		<< "In this game, you will have to progress through " << dungeonName <<
		"'s levels while defending yourself against various enemies.\nFortunately, not all levels"
		<< " are filled with monsters, and you will sometimes be able to heal yourself or collect"
		<< " items to help you on your adventure.\n"
		<< "To navigate, simply type the action you wish to perform from the list that will be"
		<< " displayed before each input.\n Have fun!\n"
		<< "-------------------------------------------------------------------------------------\n\n";

		classSelection();
	}

	void realGame() {
		for (size_t i = 0; i < 1; i++)
		{
			gameCounter++;	
			launchGame();
		}
	}
};