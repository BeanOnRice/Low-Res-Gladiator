/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: High level overview of Low Res Gladiator game
*/

#include <iostream>

enum mode { HOME, BATTLE, HSCORE, QUIT };

void _mainMenu(void);  //FIXME: needs looks touch up  // display
mode mainMenu(void);  //FIXME: needs looks touch up

int main(int argc, char **argv)
{
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
	//TITLE
	std::cout << "START\nHIGH SCORE\nQUIT\n" << std::endl;
	return;
}
