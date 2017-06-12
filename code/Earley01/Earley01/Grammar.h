#pragma once

#include "Rule.h"

class Grammar
{
private:
	std::string start_symbole;
	std::list<std::string> terminals;
	std::list<Rule> rules;

public:
	Grammar();
	void add_rule(std::string main_symbole, std::list<std::string> body);
	void add_terminal_symbole(std::string name);
};

