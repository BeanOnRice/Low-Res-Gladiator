/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: High level overview of Low Res Gladiator game
*/

#include <iostream>
#include "combat.h"

enum mode { HOME, BATTLE, HSCORE, QUIT };


void _mainMenu(void);  //FIXME: needs looks touch up  // display
mode mainMenu(void);  //FIXME: needs looks touch up

void _battle(combat *cur_combat);  //FIXME: needs looks touch up  // display
mode _gameOver(void)
mode battle(/* pointer to hs file */);  //FIXME: needs implementation finished

mode highScore(/*pointer to high score file*/);

int main(int argc, char **argv)
{
	//FIXME: open high score file
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
				std::cout << "BATTLE\n"; //FIXME
				break;
			case HSCORE:
				std::cout << "HSCORE\n"; //FIXME
				break;
			case QUIT:
				//FIXME
				std::cout << "\033[2J\033[1;1H" << "Thanks for playing!\n" << std::endl;
				return 0;
			default:
				std::cout << "Catastrophic error in main.cpp\nQuitting...\n";
				return 1;
		}
	}

	return 0;
}


mode mainMenu(void)
{
	int selection;
	std::string garbage;

	_mainMenu();
	std::cout << "\nSelection: ";

	while (!(std::cin >> selection) || (selection < 1) || (selection > 3))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		_mainMenu();
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

void _mainMenu(void)
{
	std::cout << "\033[2J\033[1;1H";
	//FIXME:TITLE
	std::cout << "START\nHIGH SCORE\nQUIT\n" << std::endl;
	return;
}


mode battle(/* pointer to hs file */)
{
	//FIXME:open file to save score to
	combat cur_combat();
	while (!cur_combat.defeat())
	{
		roundStart();
		roundEnd();
		if (cur_combat.victory())
		{
			//FIXME:levelUp player
			//FIXME:heal player
			if (((cur_combat.getRound() % 3) == 0) && (cur_combat.getRound != 0) && ((cur_combat.getRound & 10) != 0))
			{
				//FIXME:add random enemy using round + 1
			}
			else if (/*specific round*/)
			{
				//FIXME: add boss enemy
			}
			else
			{
				//FIXME:add random enemy using round
			}
			cur_combat.increaseScore();
		}
	}
	//FIXME: add score to highscore list where it needs to go
	return _gameOver();
}

void _battle(combat *cur_combat)
{
	//display
	return;
}

mode _gameOver(void)
{
	int selection;
	//FIXME: display game over screen
	//FIXME: take player input
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


mode highScore(/*pointer to high score file*/)
{
	int selection;
	//FIXME: display top 10 high scores
	//FIXME: take player input // just press anything to return home
	return HOME;
}
