/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Provides interface for user of Low Res Gladiator game
*/
//NOTE: needs file hs.txt to be in same directory (or folder)

#include <iostream>
#include <fstream>
#include "fighter.h"
#include <time.h>
#include <string>

// Default terminal rows and columns for most terminals
#define DEF_TERM_ROW 24
#define DEF_TERM_COL 80

void centerPrint(const std::string str, const int offset = 0, const int spaces_used = 0);

enum mode { HOME, BATTLE, HSCORE, QUIT };


void _mainMenuDisplay(void);
mode mainMenu(void);

mode _gameOver(void);
void _gameOverDisplay(void);  //FIXME: needs looks touch up
void _battleDisplay(const fighter *player, const fighter *enemy, bool print_usage = false);
mode battle(const std::string *hs_file_name);

void _highScoreDisplayTopTen(const std::string *hs_file_name);  //FIXME: needs looks touch up
mode highScore(const std::string *hs_file_name);

int main(int argc, char **argv)
{
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
				std::cout << "\033[2J\033[1;1H" << "\n" << std::endl << "Thanks for playing!\n" << std::endl;
				return 0;
				break;
			default:
				std::cout << "Catastrophic error in main.cpp\nQuitting...\n";
				return 1;
				break;
		}
	}

	return 2;
}


mode mainMenu(void)
{
	int selection;
	std::string garbage;

	_mainMenuDisplay();
	std::cout << "\n";
	centerPrint("Selection: ");

	while (!(std::cin >> selection) || (selection < 1) || (selection > 3))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		_mainMenuDisplay();
		centerPrint("usage: int between 1 and 3 (inclusive)");
		std::cout << "\n";
		centerPrint("Selection: ");
	}
	getline(std::cin, garbage);
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
	std::cout << "\033[2J\033[1;1H";
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
	centerPrint(title[0], -3);
	std::cout << "\n";
	centerPrint(title[1], -3);
	std::cout << "\n";
	centerPrint(title[2], -2);
	std::cout << "\n";
	centerPrint(title[3], -2);
	std::cout << "\n";
	centerPrint(title[4], -1);
	std::cout << "\n";
	for (int i = 5; i < 9; i++)
	{
		centerPrint(title[i]);
		std::cout << "\n";
	}
	std::cout << "\n\n";
	centerPrint("START");
	std::cout << "\n";
	std::cout << "\n";
	centerPrint("HIGH SCORE");
	std::cout << "\n";
	std::cout << "\n";
	centerPrint("QUIT");
	std::cout << "\n";
	std::cout << "\n";
	std::cout << std::endl;
	return;
}


mode battle(const std::string *hs_file_name)
{
	std::string garbage;
	int selection;

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
		_battleDisplay(player, enemy);
		while (!(std::cin >> selection) || (selection < 1) || (selection > player->getMoveCount()))
		{
			std::cin.clear();
			getline(std::cin, garbage);
			_battleDisplay(player,enemy, true);
		}
		getline(std::cin, garbage);
		player->chooseMove(selection + 1);

		if (enemy->getHP() > 0)
		{
			enemy->useMove(player);
			enemy->processStatusEffects();
		}
		player->processStatusEffects();
		if (enemy->getHP() <= 0)
		{
			delete enemy;
			score += round * round;
			// player level up
			player->changeHP(2);
			player->changeHP(rand() % 2);
			player->changeATK(rand() % 2);
			player->changeDEF(rand() % 2);

			enemy = new fighter((rand() % round) + 3, (rand() % round) + 1, (rand() % round + 1));
			for (int i = 0; i < 3; i++)
			{
				enemy->addRandMove((round / 3) + 2);
			}
		}
	}
	delete player;
	delete enemy;
	//FIXME: add score into highscore list
	//FIXME: sort highscore list as well
	//FIXME: highscore list CANT go over 10 entries
	return _gameOver();
}

void _battleDisplay(const fighter *player, const fighter *enemy, bool print_usage)
{
	std::string tmp;
	std::cout << "\033[2J\033[1;1H";
	std::string line[DEF_TERM_ROW];
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
	centerPrint(art[0], -3);
	std::cout << "\n";
	centerPrint(art[1], -2);
	std::cout << "\n";
	for (int i = 2; i < 7; i++)
	{
		centerPrint(art[i]);
		std::cout << "\n";
	}
	centerPrint(art[7], -1);
	std::cout << "\n";
	centerPrint(art[8]);
	std::cout << "\n";
	centerPrint(art[9]);
	std::cout << "\n";

	std::string menu[14];
	menu[0] = "";
	for (int i = 0; i < DEF_TERM_COL; i++)
	{
		menu[0] += ">";
	}
	std::cout << menu[0] << std::endl;

	menu[1] = "HP ";
	for (int i = 0; ((i < enemy->getHP()) && (i < 75)); i++)
	{
		menu[1] += "#";
	}
	std::cout << menu[1] << std::endl;  // left

	menu[2] = "BLOCK ";
	for (int i = 0; ((i < enemy->getBlocking()) && (i < 48)); i++)
	{
		menu[2] += "#";
	}
	tmp = "USING ";
	tmp += enemy->getMoveName();
	tmp += " ";
	tmp += std::to_string(enemy->getMoveStrength());
	std::cout << menu[2];  // left
	centerPrint(tmp, 999, menu[2].length());  // right
	std::cout << "\n";

	menu[3] = "POISONED ";
	for (int i = 0; ((i < enemy->getPoisoned()) && (i < 69)); i++)
	{
		menu[3] += "#";
	}
	std::cout << menu[3] << std::endl;  // left

	menu[4] = "";
	for (int i = 0; i < DEF_TERM_COL; i++)
	{
		menu[4] += "<";
	}
	std::cout << menu[4] << std::endl;

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
	std::cout << menu[5];  // left
	centerPrint(tmp, 999, menu[5].length());  // right
	std::cout << "\n";

	menu[6] = "";
	for (int i = 0; ((i < player->getBlocking()) && (i < 72)); i++)
	{
		menu[6] += "#";
	}
	menu[6] += " BLOCK";
	centerPrint(menu[6], 999);  // right
	std::cout << "\n";

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
	std::cout << menu[7];  // left
	centerPrint(tmp, 999, menu[7].length());  // right
	std::cout << "\n";

	menu[8] = "";
	std::cout << menu[8] << std::endl;  // left

	menu[9] = "3) ";
	menu[9] += player->getMoveName(2);
	menu[9] += " ";
	menu[9] += std::to_string(player->getMoveStrength(2));
	std::cout << menu[9] << std::endl;  // left

	menu[10] = "";
	std::cout << menu[10] << std::endl;  // left

	if (print_usage == true)
	{
		menu[11] = "usage: <int> in range 1 to 3 (inclusive)";
	}
	else
	{
		menu[11] = "";
	}
	std::cout << menu[11] << std::endl;

	menu[12] = "Choose a move: ";
	std::cout << menu[12];

	return;
}

mode _gameOver(void)
{
	int selection;
	std::string garbage;
	_gameOverDisplay();
	centerPrint("Selection: ");
	while (!(std::cin >> selection) || (selection < 1) || (selection > 3))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		_gameOverDisplay();
		centerPrint("usage: int between 1 and 3 (inclusive)");
		std::cout << "\n";
		centerPrint("Selection: ");
	}
	getline(std::cin, garbage);
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
	std::cout << "\033[2J\033[1;1H";
	std::cout << "\n" << std::endl;
	centerPrint("GAME");
	std::cout << "\n";
	centerPrint("OVER");
	std::cout << "\n";
	std::cout << "\n";
	centerPrint("Play again?");
	std::cout << "\n";
	std::cout << std::endl;
	centerPrint("High Scores");
	std::cout << "\n";
	std::cout << std::endl;
	centerPrint("Main Menu");
	std::cout << "\n";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}


mode highScore(const std::string *hs_file_name)
{
	std::string garbage;
	_highScoreDisplayTopTen(hs_file_name);
	centerPrint("Enter anything to return home ");
	getline(std::cin, garbage);
	return HOME;
}

void _highScoreDisplayTopTen(const std::string *hs_file_name)
{
	std::cout << "\033[2J\033[1;1H";
	/*
	std::string read_str;
	std::string disp_str;
	for (int i = 0; ((i < 10) && (*hs_file_name >> read_str)); i++)
	{
		disp_str = "Score: " + read_str;
		centerPrint(disp_str);
		std::cout << "\n";
		i++;
	}
	*/
	return;
}


void centerPrint(const std::string str, const int offset, const int space_used)
{
	int avail_space =  DEF_TERM_COL - space_used;
	if (str.length() >= avail_space)
	{
		for (int i = 0; i < DEF_TERM_COL; i++)
		{
			std::cout << str[i];
		}
	}
	else
	{
		int middle = avail_space / 2;
		int str_offset = ((str.length() - 2) / 2) * -1;
		int total_offset = str_offset + offset + middle;
		if (total_offset + str.length() > avail_space)
		{
			total_offset -= (total_offset + str.length() - avail_space);
		}
		for (int i = 0; i < total_offset; i++)
		{
			std::cout << " ";
		}
		std::cout << str;
	}
	return;
}
