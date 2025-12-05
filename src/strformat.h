/* 
File: strformat.h
Author: Jesus Treto jr.
Date: 12/5/25
Description: formatting class header, allowing strings to be centered for a terminal of x columns (x defined on class creation but can be later changed) and for clear printing (no accidental new lines) for terminal of x columns
*/

#pragma once
#include <string>
#include <iostream>

class strformat
{
public:
	strformat(int row = 24, int col = 80);  // inits with common terminal size by default
	std::string centerStr(const std::string str, const int offset = 0) const;
	void addStr(const std::string str);
	void clearStr(void) { this->str = ""; this->space_used = 0; };
	void printStr(void) const { print(this->str); };
	void print(const std::string str) const;
	void centerPrint(const std::string str, const int offset = 0) const;

	void setRow(int row) { row > 0 ? this->row = row : this->row = 1; };
	int getRow(void) const { return this->row; };
	void setCol(int col) { col > 0 ? this->col = col : this->row = 1; };
	int getCol(void) const { return this->col; };
private:
	std::string str;
	int space_used;
	int row;
	int col;
};
