#pragma once

#include<string>
#include<list>

class Rule
{
private:
	std::string main_symbole;
	std::list<std::list<std::string> > bodies;

public:

	Rule(std::string main_symbole);
	void add_a_body(std::list<std::string> body);
	void print_rule();
	std::string get_main_symbole();
};

