/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Provides interface for user of Low Res Gladiator game
*/

#include <iostream>
#include <fstream>
#include "fighter.h"
#include "strformat.h"
#include <time.h>
#include <string>
#include <vector>

// Default terminal rows and columns for most terminals
// Everything related to terminal size uses these since methods for finding terminal size vary depending on OS and terminal used
#define DEF_TERM_ROW 24
#define DEF_TERM_COL 80

enum mode { HOME, BATTLE, HSCORE, QUIT };

// utility functions
void clearScreen(void);
int getInt(const std::string prompt = "Enter an int: ", const std::string usage = "usage: <int>");  // prompts and gets int from user. Prints usage message and tries again if input invalid
int getIntInRange(int start, int end, const std::string prompt = "", const std::string usage = "");  // prompts and gets int inside of range start-end (inclusive), prints usage message and tries again if input invalid

// menu functions. '_' at front means built for function starting with same word
mode mainMenu(void);
void _mainMenuDisplay(void);

mode battle(const std::string *hs_file_name);
void _battleEnemyDisplay(void);
void _battleVictoryDisplay(void);
void _battleMenu(const fighter *player, const fighter *enemy);

mode gameOver(void);
void _gameOverDisplay(void);

mode highScore(const std::string *hs_file_name);
void _highScoreDisplay(const std::string *hs_file_name);


int main(int argc, char **argv)
{
	strformat frm;
	clearScreen();
	srand(time(nullptr));
	std::string hs_file_name = "hs.txt";
	mode cur_mode = HOME;
	while (true)
	{
		switch (cur_mode)
		{
			case HOME:
				cur_mode = mainMenu();
				break;
			case BATTLE:
				cur_mode = battle(&hs_file_name);
				break;
			case HSCORE:
				cur_mode = highScore(&hs_file_name);
				break;
			case QUIT:
				clearScreen();
				std::cout << "\n" << std::endl;
				frm.centerPrint("Thanks for playing!");
				std::cout << "\n\n" << std::endl;
				return 0;
				break;
			default:
				std::cout << "Catastrophic error in main.cpp\nQuitting...\n";
				return -1;
				break;
		}
	}

	return -2;  // should be unreachable
}


mode mainMenu(void)
{
	strformat frm;
	int selection;

	_mainMenuDisplay();
	std::cout << "\n";
	selection = getIntInRange(1, 3, frm.centerStr("Selection: "), frm.centerStr("usage: int between 1 and 3 (inclusive)"));

	switch (selection)
	{
		case 1:  // START corresponds to BATTLE
			return BATTLE;
			break;
		case 2:  // HIGH SCORE corresponds to HSCORE
			return HSCORE;
			break;
		case 3:  // QUIT corresponds to QUIT
			return QUIT;
			break;
		default:
			return HOME;  // This shouldn't be able to happen
			break;
	}
}

void _mainMenuDisplay(void)
{
	strformat frm;
	clearScreen();
	std::string title[9];
	title[0] = "       _     _____        __  ____  _____ ____";
	title[1] = "      | |   / _ \\ \\      / / |  _ \\| ____/ ___|";
	title[2] = "      | |  | | | \\ \\ /\\ / /  | |_) |  _| \\___ \\ ";
	title[3] = "      | |__| |_| |\\ V  V /   |  _ <| |___ ___) |";
	title[4] = "  ____|_____\\___/  \\_/\\_/ ___|_| \\_\\_____|____/____";
	title[5] = " / ___| |      / \\  |  _ \\_ _|  / \\|_   _/ _ \\|  _ \\ ";
	title[6] = "| |  _| |     / _ \\ | | | | |  / _ \\ | || | | | |_) |";
	title[7] = "| |_| | |___ / ___ \\| |_| | | / ___ \\| || |_| |  _ <";
	title[8] = " \\____|_____/_/   \\_\\____/___/_/   \\_\\_| \\___/|_| \\_\\";
	std::cout << std::endl;
	frm.centerPrint(title[0], -3);
	std::cout << "\n";
	frm.centerPrint(title[1], -3);
	std::cout << "\n";
	frm.centerPrint(title[2], -2);
	std::cout << "\n";
	frm.centerPrint(title[3], -2);
	std::cout << "\n";
	frm.centerPrint(title[4], -1);
	std::cout << "\n";
	for (int i = 5; i < 9; i++)
	{
		frm.centerPrint(title[i]);
		std::cout << "\n";
	}
	std::cout << "\n\n";
	frm.centerPrint("START");
	std::cout << "\n";
	std::cout << "\n";
	frm.centerPrint("HIGH SCORE");
	std::cout << "\n";
	std::cout << "\n";
	frm.centerPrint("QUIT");
	std::cout << "\n";
	std::cout << "\n";
	std::cout << std::endl;
	return;
}


mode battle(const std::string *hs_file_name)
{
	int selection;
	std::string garbage;

	fighter *player = new fighter(5, 2, 3, 3, true);
	player->addNewMove("ATTACK", "ATK", 1);
	player->addNewMove("BLOCK", "BLK", 1);
	player->addNewMove("POISON", "PSN", 2);

	fighter *enemy = new fighter();
	for (int i = 0; i < 3; i++)
	{
		enemy->addRandMove();
	}

	int round = 1;
	int score = 0;

	while (player->getHP() > 0)
	{
		enemy->chooseMove();
		_battleEnemyDisplay();
		_battleMenu(player, enemy);

		selection = getIntInRange(1, player->getMoveCount(), "Choose a move: " ,"usage: <int> in range 1 to 3 (inclusive)");
		player->chooseMove(selection - 1);

		player->useMove(enemy);

		if (enemy->getHP() > 0)
		{
			enemy->useMove(player);
			enemy->processStatusEffects();
		}
		player->processStatusEffects();
		if (enemy->getHP() <= 0)
		{
			round++;
			delete enemy;
			score += round * round;
			// player level up
			player->changeHP(rand() % 2);
			player->changeATK(rand() % 2);
			player->changeDEF(rand() % 2);
			_battleVictoryDisplay();
			_battleMenu(player, nullptr);
			getline(std::cin, garbage);

			enemy = new fighter((rand() % round) + 3, (rand() % round) + 1, (rand() % round + 1));
			for (int i = 0; i < 3; i++)
			{
				enemy->addRandMove((round / 3) + 2);
			}
		}
	}
	delete player;
	delete enemy;
	std::ofstream hs_out;
	hs_out.open(*hs_file_name, std::ofstream::out | std::ofstream::app);
	if (hs_out.is_open())
	{
		hs_out << score;
		hs_out << " ";
		hs_out.close();
	}
	else
	{
		std::cout << "Saving high score failed\n";
	}
	return gameOver();
}

void _battleMenu(const fighter *player, const fighter *enemy)
{
	strformat frm;
	std::string tmp;
	std::string line[14];

	std::string menu[14];
	menu[0] = "";
	for (int i = 0; i < DEF_TERM_COL; i++)
	{
		menu[0] += ">";
	}
	frm.print(menu[0]);
	frm.print("\n");

	if (enemy != nullptr)
	{
		menu[1] = "HP ";
		for (int i = 0; ((i < enemy->getHP()) && (i < 75)); i++)
		{
			menu[1] += "#";
		}
		frm.print(menu[1]);
		frm.print("\n");

		menu[2] = "BLOCK ";
		for (int i = 0; ((i < enemy->getBlocking()) && (i < 48)); i++)
		{
			menu[2] += "#";
		}
		tmp = "USING ";
		tmp += enemy->getMoveName();
		tmp += " ";
		tmp += std::to_string(enemy->getMoveStrength());
		frm.clearStr();
		frm.addStr(menu[2]);  // left side str
		frm.addStr(frm.centerStr(tmp, 999));  // right side str
		frm.printStr();
		frm.print("\n");

		menu[3] = "POISONED ";
		for (int i = 0; ((i < enemy->getPoisoned()) && (i < 69)); i++)
		{
			menu[3] += "#";
		}
		frm.print(menu[3]);
		frm.print("\n");
	}
	else
	{
		frm.print("\n\n\n");
	}

	menu[4] = "";
	for (int i = 0; i < DEF_TERM_COL; i++)
	{
		menu[4] += "<";
	}
	frm.print(menu[4]);
	frm.print("\n");

	if (player != nullptr)
	{
		menu[5] = "1) ";
		menu[5] += player->getMoveName(0);
		menu[5] += " ";
		menu[5] += std::to_string(player->getMoveStrength(0));
		tmp = "";
		for (int i = 0; ((i < player->getHP()) && (i < (75 - menu[5].length()))); i++)
		{
			tmp += "#";
		}
		tmp += " HP";
		frm.clearStr();
		frm.addStr(menu[5]);  // left side str
		frm.addStr(frm.centerStr(tmp, 999));  // right side str
		frm.printStr();
		frm.print("\n");

		menu[6] = "";
		for (int i = 0; ((i < player->getBlocking()) && (i < 72)); i++)
		{
			menu[6] += "#";
		}
		menu[6] += " BLOCK";
		frm.centerPrint(menu[6], 999);  // right
		frm.print("\n");

		menu[7] = "2) ";
		menu[7] += player->getMoveName(1);
		menu[7] += " ";
		menu[7] += std::to_string(player->getMoveStrength(1));
		tmp = "";
		for (int i = 0; ((i < player->getPoisoned()) && (i < 69)); i++)
		{
			tmp += "#";
		}
		tmp += " POISONED";
		frm.clearStr();
		frm.addStr(menu[7]);  // left side str
		frm.addStr(frm.centerStr(tmp, 999));  // right side str
		frm.printStr();
		frm.print("\n");

		menu[8] = "";
		frm.print(menu[8]);
		frm.print("\n");

		menu[9] = "3) ";
		menu[9] += player->getMoveName(2);
		menu[9] += " ";
		menu[9] += std::to_string(player->getMoveStrength(2));
		frm.print(menu[9]);
		frm.print("\n");

		menu[10] = "";
		frm.print(menu[10]);
		frm.print("\n");
	}
	else
	{
		frm.print("\n\n\n");
		frm.centerPrint("Player is missing!!!");
		frm.print("\n\n");
		frm.centerPrint("If you are seeing this message");
		frm.centerPrint("Just ^C the program please");
	}

	return;
}

void _battleEnemyDisplay(void)
{
	strformat frm;
	clearScreen();
	std::string art[10];
	art[0] = "                              ,.-----._";
	art[1] = "   .                         /         \\,";
	art[2] = " / \\    ,^.                Y_____        \\";
	art[3] = "/   `----\\|--'\\           .'     \\       '\"";
	art[4] = "|        ||    `>          l      \\     _l";
	art[5] = "|      __||__ /'           .|     |    ||`";
	art[6] = " \\  .-' | |  `              l     |   _.'";
	art[7] = "  \\/    | |                 l     |   j";
	art[8] = "          | |               _ \\_______/     _";
	art[9] = "           | |             / `--|    |__.--' |";
	frm.centerPrint(art[0], -3);
	std::cout << "\n";
	frm.centerPrint(art[1], -2);
	std::cout << "\n";
	for (int i = 2; i < 7; i++)
	{
		frm.centerPrint(art[i]);
		std::cout << "\n";
	}
	frm.centerPrint(art[7], -1);
	std::cout << "\n";
	frm.centerPrint(art[8]);
	std::cout << "\n";
	frm.centerPrint(art[9]);
	std::cout << "\n";
	return;
}
void _battleVictoryDisplay(void)
{
	strformat frm;
	clearScreen();
	std::cout << "\n\n\n";
	frm.centerPrint("LEVEL");
	std::cout << "\n";
	frm.centerPrint("UP!");
	std::cout << "\n\n";
	frm.centerPrint("(Input Anything)");
	std::cout << "\n\n\n\n";
	return;
}

mode gameOver(void)
{
	strformat frm;
	_gameOverDisplay();
	int selection =	getIntInRange(1, 3, frm.centerStr("Selection: "), frm.centerStr("usage: int between 1 and 3 (inclusive"));
	switch (selection)
	{
		case 1:
			return BATTLE;
			break;
		case 2:
			return HSCORE;
			break;
		case 3:
			return HOME;
			break;
		default:
			return HOME;
			break;
	}
}

void _gameOverDisplay(void)
{	
	strformat frm;
	clearScreen();
	std::cout << "\n" << std::endl;
	frm.centerPrint("GAME");
	std::cout << "\n";
	frm.centerPrint("OVER");
	std::cout << "\n";
	std::cout << "\n";
	frm.centerPrint("Play again?");
	std::cout << "\n";
	std::cout << std::endl;
	frm.centerPrint("High Scores");
	std::cout << "\n";
	std::cout << std::endl;
	frm.centerPrint("Main Menu");
	std::cout << "\n";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}


mode highScore(const std::string *hs_file_name)
{
	strformat frm;
	std::string garbage;
	_highScoreDisplay(hs_file_name);
	frm.centerPrint("Enter anything to return home ");
	std::cin >> garbage;
	getline(std::cin, garbage);
	return HOME;
}

void _highScoreDisplay(const std::string *hs_file_name)
{
	strformat frm;
	clearScreen();
	std::ifstream hs_in;
	hs_in.open(*hs_file_name);
	int tmp_int;
	std::string tmp_str;
	std::vector<int> hs_list;
	hs_list.clear();

	std::cout << "\n\n\n";
	frm.centerPrint("HIGH");
	std::cout << "\n";
	frm.centerPrint("SCORES");
	std::cout << "\n\n";
	if (hs_in.is_open())
	{
		while (hs_in >> tmp_int)
		{
			if (hs_list.size() == 0)
			{
				hs_list.push_back(tmp_int);
			}
			else
			{
				for (int i = 0; i < hs_list.size(); i++)
				{
					if (tmp_int > hs_list[i])
					{
						hs_list.insert(hs_list.begin() + i, tmp_int);
						break;
					}
					if (i == hs_list.size() - 1)  // smallest, end of list
					{
						hs_list.push_back(tmp_int);
						break;
					}
				}
			}
		}
		for (int i = 0; ((i < hs_list.size()) && (i < 10)); i++)  // Only ever display top 10 scores
		{
			tmp_str = "RANK ";
			if (i != 9)  // RANK X instead of RANK 10
			{
				tmp_str += std::to_string(i + 1);
			}
			else
			{
				tmp_str += "X";
			}
			tmp_str += ": ";
			frm.centerPrint(tmp_str, -1);
			std::cout << std::to_string(hs_list[i]);
			std::cout << std::endl;
		}
	}
	else
	{
		frm.centerPrint("No Recorded High Scores");
	}
	std::cout << "\n\n" << std::endl;

	return;
}

void clearScreen(void)
{
	std::cout << "\033[2J\033[1;1H";
	/*
	   \033 is octal escape sequence
	   [2J clears screen
	   [1;1H resets cursor to top left of terminal
	   */
	return;
}

int getInt(const std::string prompt, const std::string usage)
{
	std::string garbage;
	int input;
	std::cout << "\n" << prompt;  // \n because this function erases entire line after use
	while (!(std::cin >> input))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		std::cout << usage;
		// return cursor to where it was before user input and erases what was written after (except for the usage message)
		std::cout << "\033[1F\033[" << std::to_string(prompt.length()) << "C\033[0K";
		/*
		   \033 is octal escape sequence
		   [1F moves cursor up one row
		   [?C moves cursor right ? columns
		   [0K erases everything from cursor to end of line
		   */
	}

	std::cout << "\033[0K";  // clears usage message
	std::cout << "\033[1F\033[0K";  // clears prompt
	return input;
}


int getIntInRange(int start, int end, const std::string prompt, const std::string usage)
{
	std::string good_prompt = prompt;
	std::string good_usage = usage;
	// if no custom message was input
	if (good_prompt.compare("") == 0)
	{
		good_prompt = "enter int in range ";
		good_prompt += std::to_string(start);
		good_prompt += " - ";
		good_prompt += std::to_string(end);
		good_prompt += " (inclusive)";
	}
	if (usage.compare("") == 0)
	{
		good_usage = "usage: <int> in range ";
		good_usage += std::to_string(start);
		good_usage += " - ";
		good_usage += std::to_string(end);
		good_usage += " (inclusive)";
	}

	int input = getInt(good_prompt, good_usage);
	while ((input < start) || (input > end))
	{
		std::cout << "\033[1E" << good_usage << "\033[2F";
		input = getInt(good_prompt, good_usage);
	}

	return input;
}
