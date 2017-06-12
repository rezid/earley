#pragma once

#include<string>
#include<list>
#include<vector>

class Rule
{
private:
	std::string main_symbole;
	std::list<std::string> body;

public:
	Rule(std::string main_symbole, std::list<std::string> body);
	void print_rule();
	void print_early_rule(int position, int item_start);
	std::string get_main_symbole();
};

