#include "Rule.h"
#include<iostream>

using namespace std;

Rule::Rule(string main_symbole)
{
	this->main_symbole = main_symbole;
}

void Rule::add_a_body(list<string> body)
{
	bodies.push_back(body);
}

void Rule::print_rule()
{
	for (list<string> l : bodies) {
		cout << main_symbole << " : ";

		for (string s : l)
			cout << s << " ";

		cout << endl;
	}
}

std::string Rule::get_main_symbole()
{
	return main_symbole;
}



