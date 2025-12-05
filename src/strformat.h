/* 
File: strformat.h
Author: Jesus Treto jr.
Date: 12/5/25
Description: formatting class header, allowing strings to be centered for a terminal of x columns (x defined on class creation but can be later changed) and for clear printing (no accidental new lines) for terminal of x columns
*/

#pragma once
#include <string>

class strformat
{
Public:
	strformat(int row = 24, int col = 80);  // inits with common terminal size by default
	std::string centerStr(const::string str, const int offset = 0);
	void addToStr(const std::string *str);
	void clearStr(void) { this->str = ""; };
	void printFrt(void) const { print(this->str); };
	void print(const std::string *str) const;

	void setRow(int row) { row > 0 ? this->row = row };
	int getRow(void) const { return this->row; };
	void setCol(int col) { col > 0 ? this->col = col; };
	int getCol(void) const { return this->col; };
Private:
	std::string str;
	int space_used;
	int row;
	int col;
};
