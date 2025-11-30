/*
File: fighter.cpp
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Class for neatly holding the core stats and abilities of a fighter. Also allowing for easy checking and changing of these stats.
*/

#include "fighter.h"

fighter::fighter(int hp, int atk, int def, int moves_count, bool pc)
{
	this->stats.hp = hp;
	this->stats.atk = atk;
	this->stats.def = def;
	this->stats.is_player = pc;
	this->chosen_move = 0;

	this->moves_stocked = 0;
	if (moves_count <= 0)
	{
		this->moves_size = 1;
	}
	else
	{
		this->moves_size = moves_count;
	}
	this->moves = new move_stats[moves_size];
}

fighter::~fighter()
{
	delete[] this->moves;
}

void fighter::addNewMove(const std::string name, const std::string effect, int pwr)
{
	move_stats new_move;
	new_move.name = name;
	if (effect.compare("ATK") == 0)
	{
		new_move.effect = ATK;
	}
	else if (effect.compare("BLK"))
	{
		new_move.effect = BLK;
	}
	else if (effect.compare("PSN"))
	{
		new_move.effect = PSN;
	}
	else
	{
		new_move.effect = ATK;
	}

	new_move.pwr = pwr;

	if (this->moves_stocked >= this->moves_size)
	{
		this->moves_size *= 2;
		move_stats *tmp = new move_stats[moves_size];
		for (int i = 0; i < this->moves_stocked; i++)
		{
			tmp[i] = this->moves[i];
		}
		delete[] this->moves;
		this->moves = tmp;
	}
	this->moves[moves_stocked] = new_move;
	moves_stocked++;

	return;
}

void fighter::addRandMove(int pwr_cap)
{
	int rand_result;

	std::string name;
	int pwr = rand() % pwr_cap;
	if (pwr <= 0)
	{
		pwr = 0;
		name = "WEAK";
	}
	else if (pwr < 2)
	{
		name = "";
	}
	else if (pwr < 4)
	{
		name = "STRONG";
	}
	else
	{
		name = "COLOSSAL";
	}

	rand_result = rand() % 4;
	std::string effect;
	switch (rand_result)
	{
		case 0:
			effect = "ATK";
			name = name + " ATTACK";
			break;
		case 1:
			effect = "BLK";
			name = name + " BLOCK";
			break;
		case 2:
			effect = "PSN";
			name = name + " POISON";
			break;
		default:
			effect = "ATK";
			name = name + " ATTACKE";
			break;
	}
	addNewMove(name, effect, pwr);

	return;
}

void fighter::chooseMove(int choice)
{
	this->turn_used = false;
	if (choice >= this->moves_stocked)
	{
		this->chosen_move = rand() % this->moves_stocked;
	}
	else
	{
		this->chosen_move = choice;
	}

	if (this->moves[chosen_move].effect == BLK)
	{
		useMove();  // Blocking needs to apply pre attacking
	}

	return;
}

void fighter::useMove(fighter *target)
{
	if (this->turn_used == false)
	{
		switch (this->moves[this->chosen_move].effect)
		{
			case ATK:
				target->changeHP(target->getBlocking() - this->getMoveStrength());
				break;
			case BLK:
				this->changeBlocking(this->getMoveStrength());
				break;
			case PSN:
				target->changePoisoned(this->getMoveStrength());
				break;
		}
		this->turn_used = true;
	}

	return;
}

std::string fighter::getMoveName(int choice) const
{
	if ((choice < 0) || (choice >= this->moves_stocked))
	{
		return this->moves[this->chosen_move].name;
	}
	else
	{
		return this->moves[choice].name;
	}
	return this->moves[choice].name;
}

int fighter::getMoveStrength(int choice) const
{
	int nomination;
	if ((choice < 0) || (choice >= this->moves_stocked))
	{
		nomination = this->chosen_move;
	}
	else
	{
		nomination = choice;
	}

	switch (this->moves[nomination].effect)
	{
		case ATK:
			return (this->moves[nomination].pwr + this->stats.atk);
			break;
		case BLK:
			return (this->moves[nomination].pwr + this->stats.def);
			break;
		case PSN:
			return (this->moves[nomination].pwr + ((this->stats.hp + this->stats.def) / 3));
			break;
		default:
			return 0;
			break;
	}
}

void fighter::processStatusEffects(void)
{
	this->changeBlocking(-1);
	this->changeHP(this->getPoisoned());
	this->changePoisoned(-1);

	return;
}
