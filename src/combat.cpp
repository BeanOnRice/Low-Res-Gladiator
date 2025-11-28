#include "combat.h"

combat::combat()
{
	this->combatant_count = 2;
	this->combatants = new fighter[2];
	// init player character
	// init enemy
	this->score = 0;
}

combat::~combat()
{
	delete[] combatants;
}


void combat::addFighter(/*stats*/)
{
	// does what it says
}

void combat::levelUp(/*stat to level up*/)
{
	// increases player stat
}

void combat::roundStart()
{
	// makes npc select move
	if (/*npc move has high prio*/)
	{
		// npc move
		// player select move
		// player move
	}
	else
	{
		// player select move
		// player move
		// npc move
	}
}

void combat::roundEnd()
{
	// process end of round (see notebook)
}

bool combat::victory()
{
	if /* enemy dead + player alive? */
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool combat::defeat()
{
	if /*player dead*/
	{
		return true;
	}
	else
	{
		return false;
	}
}
