#include "Rule.h"
#include<iostream>

using namespace std;

Rule::Rule(string main_symbole, std::list<std::string> body)
{
	this->main_symbole = main_symbole;
	this->body = body;
}

void Rule::print_rule()
{
	cout << main_symbole << " : ";

	for (string s : body)
		cout << s << " ";

	cout << endl;
}

std::string Rule::get_main_symbole()
{
	return main_symbole;
}



