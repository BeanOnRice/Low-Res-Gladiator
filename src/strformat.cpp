/* 
File: strformat.cpp
Author: Jesus Treto jr.
Date: 12/5/25
Description: formatting class allowing strings to be centered for a terminal of x columns (x defined on class creation but can be later changed) and for clean printing (no accidental new lines) for terminal of x columns
*/

#include "strformat.h"

strformat::strformat(int row, int col)
{
	this->str = "";
	this->space_used = 0;
	this->row = row;
	this->col = col;
}
std::string strformat::centerStr(const std::string str, const int offset) const
{
	std::string centered_str = "";
	const int STR_LENGTH = str.length();
	if (STR_LENGTH > this->col)  // str too long
	{
		for (int i = 0; i < this->col; i++)
		{
			centered_str += str[i];
		}
	}
	else
	{
		int middle = col / 2;
		int str_offset = ((STR_LENGTH - 2) / 2) * -1;
		int total_offset = str_offset + offset + middle;
		if (total_offset + STR_LENGTH > this->col)
		{
			// stick string to right of screen
			total_offset -= (total_offset + STR_LENGTH - this->col);
		}
		for (int i = 0; i < total_offset; i++)
		{
			centered_str += ' ';
		}
		for (int i = 0; i < STR_LENGTH; i++)
		{
			centered_str += str[i];
		}
	}
	return centered_str;
}

void strformat::addStr(const std::string str)  // truncates leading ' ' from right then left of added str as needed if too long
{
	const int STR_LENGTH = str.length();
	const int AVAILABLE_SPACE = this->col - this->space_used;

	if (!(STR_LENGTH > AVAILABLE_SPACE))
	{
		for (int i = 0; i < STR_LENGTH; i++)
		{
			this->str += str[i];
			this->space_used++;
		}
	}
	else
	{
		bool left_checked = false;
		bool right_checked = false;
		int chars_to_ignore = STR_LENGTH - AVAILABLE_SPACE;
		bool *ignore = new bool[STR_LENGTH];
		for (int i = 0; i < STR_LENGTH; i++)
		{
			ignore[i] = false;
		}
		int i = STR_LENGTH - 1;  // start at end of string
		while (chars_to_ignore > 0)
		{
			if (!right_checked)
			{
				// truncate ' ' from right
				if (str[i] == ' ')
				{
					ignore[i] = true;
					chars_to_ignore--;
				}
				else
				{
					right_checked = true;
				}
			}
			else if (!left_checked)
			{
				// truncate ' ' from left
				int j = 0;
				while (chars_to_ignore > 0)
				{
					if (str[j] == ' ')
					{
						ignore[j] = true;
						chars_to_ignore--;
						j++;
					}
					else
					{
						left_checked = true;
						break;
					}
				}
				left_checked = true;
			}
			else
			{
				// truncate char from right
				ignore[i] = true;
				chars_to_ignore--;
			}
			i--;
		}
		for (int j = 0; j < STR_LENGTH; j++)
		{
			if (ignore[j] == false)
			{
				this->str += str[j];
			}
		}
		delete[] ignore;
	}
}

void strformat::print(const std::string str) const
{
	const int STR_LENGTH = str.length();
	for (int i = 0; ((i < STR_LENGTH) && (i < this->col)); i++)
	{
		std::cout << str[i];
	}
}

void strformat::centerPrint(const std::string str, const int offset) const
{
	std::string centerred_str = this->centerStr(str, offset);
	this->print(centerred_str);
}
