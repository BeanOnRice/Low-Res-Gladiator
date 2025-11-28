/*
File: fighter.h
Author: Jesus Treto Jr.
Date: 11/28/25
Description: //FIXME
*/

#pragma once
#include <vector>

struct Fighter_stats
{
	bool isPlayer = false;
	int hp = 3;   // 0 means death
	int atk = 1;  // means base damage dealt
	int def = 1;  // means damage blocked
	int mag = 0;  // mana, charge up by 1 each turn when casting a spell

	// processed at end of each round
	int blocking = 0;  // take damage here first, set to 0 end of round
				// dmg past 0 hits hp
	int poisoned = 0;  // remove this much hp and lower by 1 (down to 0)
}

enum Move_type { TACTIC, ATTACK, MAGIC };
enum Effect_type { ATK, BLK, PSN };

struct Move_stats
{
	string name = "placeholder";
	Effect_type effect = ATK;
	int pwr = 1;  // this + base_stat = effect strength
}

class Fighter
{
public:
	Fighter(bool pc = false, int hp = 3, int atk = 1, int def = 1, int moves = 3);
	void use_move(int choice = -1);
private:
	Fighter_stats stats;
	std::vector<Move_stats> moves;
}
