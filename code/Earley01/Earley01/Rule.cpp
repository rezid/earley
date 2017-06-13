#include "Rule.h"
#include<iostream>

using namespace std;

Rule::Rule(string main_symbole, std::vector<std::string> body)
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

void Rule::print_Earley_rule(int position, int item_start)
{
	cout << main_symbole << " : ";

	int i = 0;
	bool dot_insered = false;
	for (auto s : body) {
		if (i == position) {
			cout << ".";
			dot_insered = true;
		}
		cout << s << " ";
		++i;
	}

	if (!dot_insered)
		cout << ". ";
	cout << "(" << item_start << ")" << endl;
}

string Rule::get_main_symbole()
{
	return main_symbole;
}

string Rule::get_symbole(int symbole_offset)
{
	if (symbole_offset == body.size())
		return "";

	return body[symbole_offset];
}



