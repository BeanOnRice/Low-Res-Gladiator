/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Provides interface for user of Low Res Gladiator game
*/
//NOTE: needs file hs.txt to be in same directory (or folder)

#include <iostream>
#include <fstream>
//#include "combat.h"//FIXME
#include <time.h>
#include <string>

// Default terminal rows and columns for most terminals
#define DEF_TERM_ROW 24
#define DEF_TERM_COL 80

void centerPrint(std::string str, int offset = 0);

enum mode { HOME, BATTLE, HSCORE, QUIT };


void _mainMenuDisplay(void);  //FIXME: needs looks touch up  // display
mode mainMenu(void);  //FIXME: needs looks touch up

mode _gameOver(void);
void _gameOverDisplay(void);
void _battleDisplay(combat *cur_combat);  //FIXME: needs looks touch up  // display
mode battle(std::fstream hs_file_ref);  //FIXME: needs implementation finished

void _highScoreDisplayTopTen(std::fstream hs_file_ref);
mode highScore(std::fstream hs_file_ref);

int main(int argc, char **argv)
{
	srand(time(nullptr));
	std::fstream hs_file;
	hs_file.open("hs.txt");
	mode cur_mode = HOME;
	while (true)
	{
		int trash;
		switch (cur_mode)
		{
			case HOME:
				cur_mode = mainMenu();
				break;
			case BATTLE:
				cur_mode = battle(hs_file);
				break;
			case HSCORE:
				cur_mode = highScore(hs_file);
				break;
			case QUIT:
				std::cout << "\033[2J\033[1;1H" << "Thanks for playing!\n" << std::endl;
				hs_file.close();
				return 0;
			default:
				std::cout << "Catastrophic error in main.cpp\nQuitting...\n";
				hs_file.close();
				return 1;
		}
	}

	hs_file.close();
	return 2;
}


mode mainMenu(void)
{
	int selection;
	std::string garbage;

	_mainMenuDisplay();
	std::cout << "\nSelection: ";

	while (!(std::cin >> selection) || (selection < 1) || (selection > 3))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		_mainMenuDisplay();
		std::cout << "usage: int between 1 and 3 (inclusive)\n";
		std::cout << "Selection: ";
	}
	switch (selection)
	{
		case 1:  // START corresponds to BATTLE
			return BATTLE;
		case 2:  // HIGH SCORE corresponds to HSCORE
			return HSCORE;
		case 3:  // QUIT corresponds to QUIT
			return QUIT;
		default:
			return HOME;  // This shouldn't be able to happen
	}
}

void _mainMenuDisplay(void)
{
	std::cout << "\033[2J\033[1;1H";
	centerPrint("LOW RES GLADIATOR");
	centerPrint("START");
	centerPrint("HIGH SCORE");
	centerPrint("QUIT");
	std::cout << std::endl;
	return;
}


mode battle(std::fstream hs_file_ref)
{
	// disp ->> enem move choose (disp action) ->> player action ->>
	combat cur_combat();
	while (!cur_combat.defeat())
	{
		roundStart();
		_battleDisplay(&cur_combat);
		roundMiddle();  // grabs input from player then enemy acts
		roundEnd();
		_battleDisplay(&cur_combat);
		if (cur_combat.victory())
		{
			cur_combat.PlayerLevelUp((rand() % 2), (rand() % 2), (rand() % 2));
			cur_combat.PlayerHeal(0.3);
			if (((cur_combat.getRound() % 3) == 0) && (cur_combat.getRound != 0) && ((cur_combat.getRound % 10) != 0))
			{
				cur_combat.addRandomEnemy(cur_combat.getRound() + 1);
			}
			/*
			else if (//specific round)
			{
				//FIXME: add boss enemy
			}
			*/
			else
			{
				cur_combat.addRandomEnemy(cur_combat.getRound());
			}
			cur_combat.increaseScore();
		}
	}
	cur_combat.getScore() >> *hs_file_ref;
	//FIXME: sort highscore list as well
	//FIXME: highscore list CANT go over 10 entries
	return _gameOver();
}

void _battleDisplay(combat *cur_combat)
{
	//display
	return;
}

mode _gameOver(void)
{
	int selection;
	std::string garbage;
	_gameOverDisplay();
	std::cout << "Selection: ";
	while (!(std::cin >> selection))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		_gameOverDisplay();
		std::cout << "usage:: int between 1 and 3 (inclusive)\n";
		std::cout << "Selection: ";
	}
	switch (selection)
	{
		case 1:
			return BATTLE;
		case 2:
			return HSCORE;
		case 3:
			return HOME;
		default:
			return HOME;  // in case something went wrong
	}
}

void _gameOverDisplay(void)
{	
	std::cout << "\033[2J\033[1;1H";
	centerPrint("GAME");
	centerPrint("OVER");
	std::cout << "\n";
	centerPrint("Play again?");
	std::cout << std::endl;
	centerPrint("High Scores");
	std::cout << std::endl;
	centerPrint("Main Menu");
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}


mode highScore(std::fstream hs_file_ref)
{
	std::string tmp;
	_highScoreDisplayTopTen(hs_file_ref);
	centerPrint("Enter anything to return home");
	std::cin >> tmp;
	return HOME;
}

void _highScoreDisplayTopTen(std::fstream hs_file_ref)
{
	std::string read_str;
	std::string disp_str;
	int i = 0;
	while ((*hs_file_ref >> read_str) && (i < 10))
	{
		disp_str = "Score: " + read_str;
		centerPrint(disp_str);
		i++;
	}
	return;
}


void centerPrint(std::string str, int offset)
{
	if (str.length() >= DEF_TERM_COL)
	{
		for (int i = 0; i < DEF_TERM_COL; i++)
		{
			std::cout << str[i];
		}
		std::cout << std::endl;
	}
	else
	{
		int middle = DEF_TERM_COL / 2;
		int str_offset = ((str.length() - 2) / 2) * -1;
		int total_offset = str_offset + offset + middle;
		if (total_offset + str.length() > DEF_TERM_COL)
		{
			total_offset -= (total_offset + str.length() - DEF_TERM_COL);
		}
		for (int i = 0; i < total_offset; i++)
		{
			std::cout << " ";
		}
		std::cout << str << std::endl;
	}
	return;
}
