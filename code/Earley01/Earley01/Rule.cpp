#include "Rule.h"
#include<iostream>

using namespace std;

Rule::Rule()
{
	main_symbole_is_set = false;
}

Rule::Rule(string main_symbole, std::vector<std::string> body)
{
	this->main_symbole = main_symbole;
	this->body = body;
	main_symbole_is_set = true;
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

bool Rule::set_main_symbole(std::string main_symbole)
{
	if (main_symbole_is_set)
		return false;

	this->main_symbole = main_symbole;
	return true;
}

void Rule::set_body(std::vector<std::string> body)
{
	this->body = body;
}

bool Rule::push_back_symbole_to_body(std::string symbole)
{
	if (symbole == ";" && body.size() == 0)
		return false;

	if (symbole != ";")
		body.push_back(symbole);

	return true;
}

void Rule::clear_rule()
{
	main_symbole.clear();
	body.clear();
	main_symbole_is_set = false;
}

bool Rule::operator==(const Rule& rule) const
{
	if (main_symbole == rule.main_symbole && body == rule.body)
		return true;

	return false;
}



