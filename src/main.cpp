/*
File: main.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: High level overview of Low Res Gladiator game
*/

#include <iostream>

enum mode { HOME, BATTLE, HSCORE, QUIT }

void _mainMenu();  //FIXME: needs looks touch up  // display
mode mainMenu();  //FIXME: needs looks touch up

int main(int argc, char **argv)
{
	mode cur_mode = HOME;
	while (true)
	{
		switch (mode)
		{
			case HOME:
				{
					//FIXME: main menu
					break;
				}
			case BATTLE:
				{
					std::cout << "BATTLE\n"; //FIXME
					break;
				}
			case HSCORE:
				{
					std::cout << "HSCORE\n"; //FIXME
					break;
				}
			case QUIT:
				{
					//FIXME
					std::cout << "\033[2J\033[1;1H" << "Thanks for playing!" << std::endl;
					return 0;
				}
			case default:
				{
					std::cout << "Catastrophic error in main.cpp\nQuitting...\n";
					return 1;
				}
			cur_mode = HOME;  //FIXME: REMOVE when functions done
		}

	return 0;
}


mode mainMenu()
{
	int selection;
	bool usage_displayed = false;
	string garbage;

	_mainMenu();
	std::cout << "Selection: ";

	while (!(std::cin >> selection) || (selection < 1) || (selection > 3))
	{
		std::cin.clear();
		getline(std::cin, garbage);
		if (usage_displayed == false)
		{
			_mainMenu();
			std::cout << "usage: int between 1 and 3 (inclusive)\n";
			std::cout << "Selection: ";
			usage_displayed == true;
		}
	}
	switch (selection)
	{
		case 1:  // START corresponds to BATTLE
			return BATTLE;
		case 2:  // HIGH SCORE corresponds to HSCORE
			return HSCORE;
		case 3:  // QUIT corresponds to QUIT
			return QUIT;
		case default:
			return HOME;  // This shouldn't be able to happen
	}
}

void _mainMenu()
{
	std::cout << "\033[2J\033[1;1H";
	//TITLE
	std::cout << "START\nHIGH SCORE\nQUIT\n" << std::endl;
	return;
}
