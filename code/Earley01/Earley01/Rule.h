#pragma once

#include<string>
#include<list>

class Rule
{
private:
	std::string start;
	std::list<std::list<std::string> > bodies;

public:

	Rule(std::string start);
	void add_a_body(std::list<std::string> body);
};

