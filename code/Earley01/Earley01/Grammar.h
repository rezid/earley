#pragma once

#include "Rule.h"

class Grammar
{
private:
	std::string start_symbole;
	std::list<Rule> rules;

public:
	Grammar();
	void add_a_rule(std::string main_symbole, std::list<std::string> body);
};

