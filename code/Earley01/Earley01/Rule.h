#pragma once

#include<string>
#include<vector>

class Rule
{
private:
	std::string main_symbole;
	std::vector<std::string> body;

public:
	Rule(std::string main_symbole, std::vector<std::string> body);
	void print_rule();
	void print_Earley_rule(int position, int item_start);
	std::string get_main_symbole();
	std::string get_symbole(int symbole_offset);
};

