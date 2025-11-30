/*
File: fighter.h
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Class for neatly holding the core stats and abilities of a fighter. Also allowing for easy checking and changing of these stats.
*/

#pragma once
#include <vector>

struct fighter_stats
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

//FIXME: NEW prio just player first, then enemy
enum effect_type { ATK, BLK, PSN };

struct move_stats
{
	std::string name = "placeholder";
	effect_type effect = ATK;
	int pwr = 1;  // this + fighter base_stat = effect strength
}

class fighter
{
public:
	// Initializing
	fighter(int hp = 3, int atk = 1, int def = 1, int moves = 3, bool pc = false);  //FIXME: make .cpp match
	void addNewMove(std::string name = "Basic attack", effect_type effect = ATK, int pwr = 1);
	void addRandomNewMove(void);  // for giving enemy random moves

	// Moves
	void ChooseRandMove(void);  // selects random move  //FIXME: NEW
	void useMove(void);  // uses selected move  //FIXME: NEW
	std::string getMoveName(void) { return this->moves[chosen_move].name; };
	effect_type getMoveEffect(void) { return this->moves[chosen_move].effect; };
	int getMovePwr(void) { return this->moves[chosen_move].pwr; };
	int getMovesAmount(void) { return this->moves.size(); };

	// Core stats
	bool player(void) { return this->stats.isPlayer; };
	void setHP(int hp) { this->stats.hp = hp; };
	int getHP(void) { return this->stats.hp; };
	void setATK(int atk) { this->stats.atk = atk; };
	int getATK(void) { return this->stats.atk; };
	void setDEF(int def) { this->stats.def = def; };
	int getDEF(void) { return this->stats.def; };
	void setMAG(int mag) { this->stats.mag = mag; };
	int getMAG(void) { return this->stats.mag; };
	// Status effects
	void setBlocking(int block) { this->stats.blocking = block; };
	int getBlocking(void) { return this->stats.blocking; };
	void setPoisoned(int pois) { this->stats.poisoned = pois; };
	int getPoisoned(void) { return this->stats.poisoned; };

private:
	fighter_stats stats;
	std::vector<Move_stats> moves;
	int chosen_move;  //FIXME: NEW
}
