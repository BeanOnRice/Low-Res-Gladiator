/*
File: fighter.h
Author: Jesus Treto Jr.
Date: 11/28/25
Description: Class for neatly holding the core stats and abilities of a fighter. Also allowing for easy checking and changing of these stats.
*/

#pragma once
#include <string>

struct fighter_stats
{
	bool is_player = false;
	int hp = 3;   // 0 means death
	int atk = 1;  // means base damage dealt
	int def = 1;  // means damage blocked

	// processed at end of each round
	int blocking = 0;  // take damage here first, lowered end of round
	int poisoned = 0;  // remove this much hp
};

enum effect_type { ATK, BLK, PSN };

struct move_stats
{
	std::string name = "placeholder";
	effect_type effect = ATK;
	int pwr = 1;  // pwr + fighter base_stat = effect strength
};

class fighter
{
public:
	// Initializing
	fighter(int hp = 3, int atk = 1, int def = 1, int moves = 3, bool pc = false);
	~fighter();
	void addNewMove(std::string name = "Basic Attack", effect_type effect = ATK, int pwr = 1);
	void addRandMove(int pwr_cap = 2);

	// Moves
	int getMoveCount(void) { return this->moves_stocked; };
	void chooseMove(int choice = -1);  // chooses random by default
	void useMove(fighter *target);
	std::string getMoveName(int choice = -1);  // no param gives move chosen by npc
	int getMoveStrength(int choice = -1);  // no param gives move chosen by npc

	// Stat changers
	void changeHP(int change) { this->stats.hp += change; };
	void changeATK(int change) { this->stats.atk += change; };
	void changeDEF(int change) { this->stats.def += change; };
	void changeBlocking(int change) { this->stats.blocking += change; };
	void changePoisoned(int change) { this->stats.poisoned += change; };

	// Core stats
	bool isPlayer(void) { return this->stats.is_player; };
	void setHP(int hp) { this->stats.hp = hp; };
	int getHP(void) { return this->stats.hp; };
	void setATK(int atk) { this->stats.atk = atk; };
	int getATK(void) { return this->stats.atk; };
	void setDEF(int def) { this->stats.def = def; };
	int getDEF(void) { return this->stats.def; };
	// Status effects
	void processStatusEffects(void);
	void setBlocking(int block) { this->stats.blocking = block; };
	int getBlocking(void) { return this->stats.blocking; };
	void setPoisoned(int pois) { this->stats.poisoned = pois; };
	int getPoisoned(void) { return this->stats.poisoned; };

private:
	fighter_stats stats;
	move_stats *moves = nullptr;
	int moves_stocked = 0;
	int moves_size = 0;
	int chosen_move = 0;
	bool turn_used = false;
};
