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
	std::list<std::string> npcEncountered;

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
		playerCharacter.resetCharacter();
		floorLevel = 0;
		combatCounter = 0;
		enemiesSlain = 0;
		treasuresFound = 0;
		npcEncountered.clear();
	}

	std::string lowercaseString(std::string text) {
		std::string response = text;
		std::transform(response.begin(), response.end(), response.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return response;
	}

	std::string uppercaseString(std::string text) {
		std::string response = text;
		std::transform(response.begin(), response.end(), response.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return response;
	}

	std::string capitalizeString(std::string text) {
		std::string response = text;
		if (response != "") {
			response[0] = toupper(response[0]);
		}
		return response;
	}

	std::string numberSufix(int number) {
		if (number % 10 == 1) {
			return "st";
		}
		else if (number % 10 == 2) {
			return "nd";
		}
		else {
			return "th";
		}
	}

	void userCopyInput(std::string textToDisplay, std::string textToCopy) {
		std::string response = "";
		bool validResponse = false;

		while (!validResponse) {
			std::cout << textToDisplay << "\n - "<< textToCopy <<"\n\n" << playerCharacter.getName() << "> ";
			std::cin >> response;

			if (!std::cin.fail() && lowercaseString(response) == lowercaseString(textToCopy)) {
				validResponse = true;
			}
			else {
				std::cout << "\n~ Incorrect input. ~\n";
			}
		}

		std::cout << "\n";
	};

	std::string userTextInput() {
		std::string response;

		std::cout << "\n" << playerCharacter.getName() << "> ";
		std::cin >> response;

		std::cout << "\n";
		return response;
	};

	std::string userTextInput(std::string textToDisplay) {
		std::string response = "";
		bool validResponse = false;

		while (!validResponse) {
			std::cout << textToDisplay << "\n\n" << playerCharacter.getName() << "> ";
			std::cin >> response;

			if (!std::cin.fail()) {
				validResponse = true;
			}
			else {
				std::cout << "\n~ Incorrect input. ~\n";
			}
		}

		std::cout << "\n";
		return response;
	};

	std::string userTextInput(std::string textToDisplay, std::list<std::string> possibleResponses) {
		std::string response = "";
		std::string possibilities = "";
		std::list<std::string> lowerCaseResponses;
		bool validResponse = false;

		int iterator = 0;
		for (std::string p : possibleResponses) {
			iterator++;
			possibilities += " - " + std::to_string(iterator) + " : " + p + "\n";
			lowerCaseResponses.push_back(lowercaseString(p));
		}

		while (!validResponse) {
			std::cout << textToDisplay << "\n" << possibilities << "\n" << playerCharacter.getName() << "> ";
			std::cin >> response;
			if (!std::cin.fail()) {
				std::transform(response.begin(), response.end(), response.begin(),
					[](unsigned char c) { return std::tolower(c); });
			}

			if (std::find(lowerCaseResponses.begin(), lowerCaseResponses.end(), response) != lowerCaseResponses.end()
				&& !std::cin.fail()) {
				validResponse = true;
			}
			else {
				std::cout << "\n~ Incorrect response. ~\n";
			}
		}
		std::cout << "\n";
		return capitalizeString(response);
	};

	bool userBoolInput(std::string textToDisplay) {
		std::string response = "";
		bool validResponse = false;

		while (!validResponse) {
			std::cout << textToDisplay << "\n"
				<< " - Yes\n - No\n\n"
				<< playerCharacter.getName() << "> ";
			std::cin >> response;
			if (!std::cin.fail()) {
				response = lowercaseString(response);
			}

			if (!std::cin.fail() && (response == "yes" || response == "y" ||
				response == "no" || response == "n")) {
				validResponse = true;
			}
			else if (response == "maybe" || response == "perhaps") {
				std::cout << "\n~ Very funny. ~\n";
			}
			else {
				std::cout << "\n~ Only respond with yes or no. ~\n";
			}
		}

		std::cout << "\n";

		if (response == "yes" || response == "y") {
			return true;
		}
		else {
			return false;
		}
	};

	std::string dungeonNameGenerator() {
		std::string prefix[] =
		{"the Magnificent", "Mr. Rat's", "the Darkest",
			"the Basic", "Magic Lord's", "the Sunken", "the High Definition"};

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

		playerCharacter.setJob(selection);
	}

	void nameSelection() {
		std::string selection = userTextInput("Then, enter your name :");
		playerCharacter.setName(capitalizeString(selection));
	}

	void treasure() {
		int randomGold = (rand() % 10) + 15;
		playerCharacter.getInventory()->addGold(randomGold);


		std::string reward = std::to_string(randomGold) + " gold";

		std::cout << "You open the treasure and found : " << reward << "\n";
		treasuresFound++;
	}

	void combatManager() {

	}

	void combatFloor() {

	}

	void dialogFloor() {
		// Encounter random generation
		int characterEncounter = rand() % 100;
		/*
		*  0 to 39 : Merkat the Merchant
		* 40 to 54 : Cornifer the Cartograph 
		* 55 to 69 : Beelzebuth the Putrid
		* 70 to 94 : Tagliatelli the Cook
		* 95 to 99 : Leon the Generous
		*/

		// Merkat
		if (characterEncounter <= 39) {
			if (std::find(npcEncountered.begin(), npcEncountered.end(), "Merkat") != npcEncountered.end()) {
				std::cout << "Merkat> Oh hi " << playerCharacter.getName() << "! As you can see, I moved "
					<< "to this floor to better my business...\n"
					<< "Merkat> But it has been too effective, I'm still out of stock! See you later!";
			}
			else {
				npcEncountered.push_back("Merkat");
				std::cout << "As " << playerCharacter.getName() << "'s surprise, this floor is filled with "
					<< "various items, all labeled with price tags. \nBefore he could make any progress, a "
					<< " large man appears from behind a pile of junk.\n";

				std::string merkat = "\nMerkat> Oh hello there! I don't believe we've met before! Name's Merkat, "
					"I'm just a simple dude trying to survive in this dungeon.\n";

				std::cout << merkat;

				userTextInput();

				merkat = "Merkat> I'm a merchant and should be selling you stuff right now, but I'm out of business, "
					"due to time constraints. Please come back at a later date.\nGood luck on your aventure however!";

				std::cout << merkat;
			}
		}
		// Cornifer
		else if (characterEncounter <= 54) {
			if (std::find(npcEncountered.begin(), npcEncountered.end(), "Cornifer") != npcEncountered.end()) {
				std::cout << "Cornifer> Still in development, go on.\n";
				if (userBoolInput("That stinks. Screw the dev.")) {
					std::cout << "Oh, give me a break, I spent so much time on the combat system.\n";
				}
				else {
					std::cout << "That's kind, thanks. Here's a treasure.\n";
					treasure();
				}
			}
			else {
				npcEncountered.push_back("Cornifer");
				std::cout << "Cornifer> Sorry dude I'm still in development, go through my floor, dude, please.\n";

				if (userBoolInput("Follow Cornifer's request?")) {
				}
				else {
					std::cout << "You don't reeally have the choice though.\n";
				}
			}
		}
		// Beelzebuth
		else if (characterEncounter <= 69) {
			if (std::find(npcEncountered.begin(), npcEncountered.end(), "Beelzebuth") != npcEncountered.end()) {
				std::cout << "Beelzbuth> Oh, it's you again adventurer! Take another treasure, help yourself!\n";
				if (userBoolInput("Take the treasure?")) {
					treasure();
				}
				else {
					std::cout << "You back off this suspicious offer... Who would take a treasure from a giant fly?\n";
				}
			}
			else {
				std::cout << "Before you could do anything, a giant fly stops your advancement and presents you with "
					<< "various weapons.\n\nBeelzbuth> Good evening adventurer! What a treat to come across your path!"
					<< " Please, take one of my treasures and go on your adventure, those wretched lands are quite "
					<< "dangerous for a human like yourself !\n";

				if (userBoolInput("Take the treasure?")) {
					treasure();
				}
				else {
					std::cout << "You back off this suspicious offer... Who would take a treasure from a giant fly?\n";
				}
			}
		}
		// Tagliatelli
		else if (characterEncounter <= 94) {
			if (std::find(npcEncountered.begin(), npcEncountered.end(), "Tagliatelli") != npcEncountered.end()) {
				std::cout << "Tagliatelli> Mamma mia " << playerCharacter.getName() << "! Would you care to taste "
					<< "another delicacy of mine ?\n";

				if (userBoolInput("Eat Tagliatelli's 'special' pasta?")) {
					if (rand() % 2 == 0) {
						int damage = (rand() % 4) + 2;
						std::cout << "The food tasted good, but you quickly realise it was not necessarily suited "
							<< "for human consumption, as you stomach violently starts hurting.\n";
						playerCharacter.takeDamage(damage);
					}
					else {
						int heal = (rand() % 8) + 13;
						std::cout << "Mamma mia! The pasta was-a very good!\n";
						playerCharacter.heal(heal);
					}
				}
				else {
					std::cout << "The coook seems disappointed with your decision... He lets out a grunt before "
						<< "resuming to cooking.\n";
				}
			}
			else {
				npcEncountered.push_back("Tagliatelli");
				std::cout << "You enter this floor only to be greeeted by a large fish-man with a strong accent, happily "
					<< "cooking pastas behind his counter.\n\nTagliatelli> Mamma mia traveler! Welcome to my kitchen!\n"
					<< " Would you be so kind to taste my latest creation? You won't regret it, I'm sure!\n";

				if (userBoolInput("Eat Tagliatelli's 'special' pasta?")) {
					if (rand() % 2 == 0) {
						int damage = (rand() % 4) + 2;
						std::cout << "The food tasted good, but you quickly realise it was not necessarily suited "
							<< "for human consumption, as you stomach violently starts hurting.\n";
						playerCharacter.takeDamage(damage);
					}
					else {
						int heal = (rand() % 8) + 13;
						std::cout << "Mamma mia! The pasta was-a very good!\n";
						playerCharacter.heal(heal);
					}
				}
				else {
					std::cout << "The coook seems disappointed with your decision... He lets out a grunt before "
						<< "resuming to cooking.\n";
				}
			}
		}
		// Leon
		else {
			if (std::find(npcEncountered.begin(), npcEncountered.end(), "Leon") != npcEncountered.end()) {
				std::cout << "You come across a known face.\n\n"
					<< "Leon> NOT YOU AGAIN! LEAVE ME ALONE!\n\n"
					<< "The man seem to have been robbed from other travelers and is sobbing in a corner of the room.\n"
					<< "Better leave him be, he has seen better days.\n";
			}
			else {
				npcEncountered.push_back("Leon");
				std::cout << "As " << playerCharacter.getName() << " steps foot on the floor, a wealthy man "
					<< " shouts at him :\n";

				if (playerCharacter.getJob() == "Thief") {
					std::cout << "Leon> Hey you! Yes, you!\n";

					std::string response = userTextInput("It's payday time!", {"Rob him","Keep listening"});

					if (lowercaseString(response) == "rob him") {
						int purseContent = 15 + rand() % 20;
						std::cout << "You jump towards the man equipped with your " << playerCharacter.getWeapon()->weaponName
							<< " in hand as he screams in terror.\nBefore you could do any harm, he tosses his purse at you\n"
							<< " and starts sobbing.\nCongrats, you just gained "<< purseContent << " coins and made a "
							<< "grown-up man cry.\n";
					}
					else {
						std::cout << "Leon> I don't trust adventurers and I have no business in fighting you!\n"
							<< "Leon> Take this and leave me alone!\n\n"
							<< "The man points to a trasure on the other side of the room. He seems very scared "
							<< "of you.\n";

						response = userTextInput("What do you do?",
							{ "Rob him","Take treasure","Both","Go away" });

						int purseContent = 15 + rand() % 20;
						if (lowercaseString(response) == "rob him") {
							std::cout << "You jump towards the man equipped with your " << playerCharacter.getWeapon()->weaponName
								<< " in hand as he screams in terror.\nBefore you could do any harm, he tosses his purse at you\n"
								<< " and starts sobbing.\nCongrats, you just gained " << purseContent << " coins and made a "
								<< "grown-up man cry.\n";
						}
						else if (lowercaseString(response) == "take treasure") {
							std::cout << "You gladly take the offering before going on with your adventure.\n";
							treasure();
						}
						else if (lowercaseString(response) == "both") {
							std::cout << "You jump towards the man equipped with your " << playerCharacter.getWeapon()->weaponName
								<< " in hand as he screams in terror.\nBefore you could do any harm, he tosses his purse at you\n"
								<< " and starts sobbing.\nYou then grab his treasure before going on with your adventure.\n"
								<< "Congrats, you just gained " << purseContent << " coins and made a "
								<< "grown-up man cry.\n";
							treasure();
						}
						else {

						}
					}
				}
				else {
					std::cout << "Leon> Hey you! Yes, you!\n";

					userTextInput();

					std::cout << "Leon> I don't trust adventurers and I have no business in fighting you!\n"
						<< "Leon> Take this and leave me alone!\n\n"
						<< "The man points to a trasure on the other side of the room. He seems very scared "
						<< "of you.\n";

					if (userBoolInput("Will you take the treasure?")) {
						std::cout << "You gladly take the offering before going on with your adventure.\n";
						treasure();
					}
					else {
						std::cout << "You do not trust this crazy man and go on with your dungeon crawling.\n";
					}

				}


			}
		}
	}

	void treasureFloor() {
		int randomN = rand() % 3 == 0;
		if (randomN == 0) {
			std::cout << "You enter a dark room filled with bones from previous adventurers. You are not sure anymore "
				<< "why you entered the dungeon in the first place.\nAs you loose fate in yourself, you see a shiny object "
				<< "reflecting light in a corner of the room. It's a treasure chest! It definitly gives you a spark of hope!\n";

			if (userBoolInput("Will you open the treasure?")) {
				std::cout << "Fortunately, this was not a trap! You take your newfound goods and leave the floor.\n";
				treasure();
			}
			else {
				std::cout << "You do not trust a treasure chest in a room full of skeletons. Sane choice.\n";
			}
		}
		else if (randomN == 1) {
			std::cout << "This floor, contrary to the rest of the dungeon, is really clean and shiny, almost heaven-like.\n"
				<< "In the center of the room lies an opened treasure chest filled with useful stuff!\n";
			treasure();
			userTextInput("Neat!");
		}
		else {
			std::cout << "You enter a glitched room, probably not finished by the developer.\nThere is a treasure chest "
				<< "in the center of it, as a sign of forgiveness.\n";
			treasure();

			if (userBoolInput("Are you still mad at the developer despite the bribe?")) {
				std::cout << "Then take this and leave!\n";
				playerCharacter.takeDamage(1);
			}
			else {
				std::cout << "You're a smart man, take another treasure for the effort.\n";
				treasure();
			}
		}
		
	}

	void dungeonCrawler() {
		do
		{
			floorLevel++;

			std::cout << "\n\n ~ ~ " << playerCharacter.getName() << " enters the "
				<< floorLevel << numberSufix(floorLevel) << " floor. ~ ~ \n\n";

			// Floor type random generation
			int floorType = rand() % 100;
			/*
			*  0 to 59 -> combat
			* 60 to 84 -> dialog
			* 85 to 98 -> treasure
			*		99 -> empty
			* Floor 1 is always a combat and every 5 floor is always a treasure
			*/

			// Combat floor
			if ((floorType <= 59 || floorLevel == 1) && floorLevel % 5 != 0) {
				combatFloor();
			}
			// Dialog floor
			else if ((floorType <= 84) && floorLevel % 5 != 0) {
				dialogFloor();
			}
			// Treasure floor
			else if ( floorType<=98 || floorLevel % 5 == 0) {
				treasureFloor();
			}
			// Empty floor
			else {
				if (userBoolInput("This floor seems empty. Would "+ playerCharacter.getName()+" take some resting time?")) {
					int firstHp = playerCharacter.getCurrentHealth();
					playerCharacter.heal(floor(playerCharacter.getMaxHealth()*0.3));
					std::cout << playerCharacter.getName() << " is now well rested and healed "
						<< playerCharacter.getCurrentHealth() - firstHp << " health points.\n";

				}
				std::cout << playerCharacter.getName() << " continues his adventure.\n";
			}
			playerCharacter.takeDamage(1);
			if (playerCharacter.getCurrentHealth() > 0) {
				std::cout << " ~ You survived another floor. ~ \n";
				playerCharacter.characChecking();
				userCopyInput(" ~ Continue when ready. ~ ", "Continue");
			}

		} while (playerCharacter.getCurrentHealth() > 0);
	}

	void launchGame() {
		dungeonName = dungeonNameGenerator();

		std::cout << "/*-- THE REAL GAME, Attempt : " << gameCounter << ", "<< capitalizeString(dungeonName) <<" --*/\n\n"
		<< "-------------------------------------------------------------------------------------\n"
		<< "In this game, you will have to progress through " << dungeonName <<
		"'s levels while defending yourself against various enemies.\nFortunately, not all levels"
		<< " are filled with monsters, and you will sometimes be able to heal yourself or collect"
		<< " items to help you on your adventure.\n"
		<< "To navigate, simply type the action you wish to perform from the list that will be"
		<< " displayed before each input.\n Have fun!\n"
		<< "-------------------------------------------------------------------------------------\n\n";

		do
		{
			playerCharacter.setName("Traveler");
			classSelection();
			nameSelection();
			playerCharacter.characChecking();
		} while (!userBoolInput("Do you want to start your adventure with this character?"));

		if (playerCharacter.getJob() == "Barbarian") {
			std::cout << "Armed with all his strength, might and greed, the bestial "
				<< playerCharacter.getName() << " enters " << dungeonName
				<< " with high hopes of finding glory and fortune.\nHe will soon realise"
				<< " his mistake as he encounters his first enemy...\n";
		}
		else if (playerCharacter.getJob() == "Arcanist") {
			std::cout << playerCharacter.getName() << ", in search of wisdom in his electrical powers, "
				<< " enters " << dungeonName
				<< ", armed with the most conductible object he could find.\nHe will soon realise"
				<< " bringing a fork to a real fight could get him in trouble...\n";
		}
		else {
			std::cout << playerCharacter.getName() << " finally finds a way to escape the guards, as he enters "
				<< dungeonName
				<< ".\nWith filled pockets and a determination to survive in this hostile environment,"
				<< " he begins his journey through the dungeon.\nHe will soon realise"
				<< " facing the law may have been his salute for once...\n";
		}

		dungeonCrawler();
		
		std::cout << "\n";
		if (playerCharacter.getJob() == "Barbarian") {
			std::cout << "Despite all his efforts, the great "
				<< playerCharacter.getName() << " couldn't survive " << dungeonName
				<< ".\n He managed to go through " << floorLevel << " floors before succumbing.\n"
				<< "\nHis memory will probably be forgotten in the mist of time...\n\n";
		}
		else if (playerCharacter.getJob() == "Arcanist") {
			std::cout << playerCharacter.getName() << ", in a last resort, used what will be his "
				<< " last spell.\n As he screams 'AUTO-DESTRUCTO-ZAP!', the " << floorLevel << numberSufix(floorLevel)
				<< " floor of " << dungeonName << " bathes in a blinding light, before exploding."
				<< "\n\nThe naive traveler finally achieved his goal, as he discovered his true power...\n\n";
		}
		else {
			std::cout << playerCharacter.getName() << " could not dodge this last hit, and as his body "
				<< "fell to the ground, all his hard-earned coins rolled from his pockets to the dungeon's "
				<< floorLevel << numberSufix(floorLevel) << " floor.\n"
				<< "\nHe smiles as he loses consciousness, knowing he finally finished fleeing...\n\n";
		}
		std::cout << " ~ ~ ~ ~ G A M E   O V E R ~ ~ ~ ~ "
			<< "\n ~ Attempt number    : " << gameCounter
			<< "\n ~ Floor reached     : " << floorLevel
			<< "\n ~ Battles survived  : " << combatCounter - 1
			<< "\n ~ Enemies slain     : " << enemiesSlain
			<< "\n ~ Treasures found   : " << treasuresFound
			<< "\n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n\n";
		playerCharacter.characChecking();

	}

	void realGame() {
		do
		{
			gameCounter++;
			resetGame();
			launchGame();
			playerCharacter.setName("");
		} while (userBoolInput("Do you want to replay the game?"));
	}
};