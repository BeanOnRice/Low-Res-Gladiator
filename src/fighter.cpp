/*
File: fighter.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: //FIXME
*/

#include "fighter.h"

Fighter::Fighter(int hp, int atk, int def, int moves)
{
	this->stats.hp = hp;
	this->stats.atk = atk;
	this->stats.def = def;
	this->stats.mag = 0;

	this->moves.erase();
	for (int i = 0; i < moves; i++)
	{
		//FIXME add a move
	}
}

void Fighter::use_move(int choice)
{
	//FIXME if choice == -1, choose random
	//FIXME read move effect and priority
		//FIXME use move
	return;
}
