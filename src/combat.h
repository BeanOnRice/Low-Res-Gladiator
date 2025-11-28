/*
File: combat.h
Author Jesus Treto Jr.
Date: 11/28/25
Description: Class for managing combat in Low Res Gladiator. Lets you add the combatants(only two combatants for this assignment), manage turn order, apply end/start of round effects, and see who won the battle
*/

#pragma once
#include "fighter.h"

class combat
{
public:
	combat();  // sets combatant_count = 2, score = 0, makes combatants, round = 0
	~combat();

	void addFighter(/*stats*/);  // for adding new enemy
	void addRandomEnemy(int stat_spread); // add random enemy spreading input stats around 
	void levelUp(/*stat to level up*/);  // for leveling up player
	void heal(/*percentage to heal*/);  //FIXME: NEW

	void roundStart();  // lets enemy choose move (see notebook)
	void roundEnd();  // clears shields, processes poison, etc

	bool victory();
	bool defeat();
	int getRound() { return this->round; };
	void increaseScore();  //FIXME: NEW
	int getScore() { return this->score; };

private:
	int combatant_count;
	fighter *combatants;

	int round;
	int score;
}
