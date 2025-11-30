/*
File: fighter.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Class for neatly holding the core stats and abilities of a fighter. Also allowing for easy checking and changing of these stats.
*/

#include "fighter.h"

fighter::fighter(int hp, int atk, int def, int moves, bool pc)
{
	this->stats.isPlayer = pc;
	this->stats.hp = hp;
	this->stats.atk = atk;
	this->stats.def = def;
	this->stats.mag = 0;

	this->moves.erase();
	for (int i = 0; i < moves; i++)
	{
		//FIXME add a move
	}
	this->chosen_move = 0;
}

void fighter::addNewMove(move_priority prio = ATTACK, std::string name = "Basic attack", effect_type effect = ATK, int pwr = 1)
{
	move_stats new_move;
	new_move.priority = prio;
	new_move.name = name;
	new_move.effect = effect;
	new_move.pwr = pwr;
	this->moves.push_back(new_move);
	return;
}

void fighter::addRandomNewMove(void)  //FIXME: make random
{
	//seed seeded in main.cpp
	move_priority prio;
	std::string name;
	effect_type effect;
	int pwr;
}

void fighter::use_move(int choice)
{
	//FIXME if choice == -1, choose random
	//FIXME read move effect and priority
		//FIXME use move
	return;
}
