#include "Grammar.h"
#include<iostream>

using namespace std;

Grammar::Grammar()
{
}

void Grammar::add_terminal_symbole(std::string name)
{
	terminals.push_back(name);
}

void Grammar::print_terminal_symboles()
{
	cout << "\nThe "<< terminals.size() <<" terminal symboles are: ";
	for (auto t : terminals)
		cout << t << " ";

	cout << "\n" << endl;
}

void Grammar::print_all_rules()
{
	cout << "\n-----------GRAMMAR RULES-----------\n";
	for (auto r : rules)
		r.print_rule();
	cout << "-----------------------------------\n" << endl;
}

void Grammar::add_rule(string main_symbole, list<string> body)
{
	// Create a new rule and add it to the grammar
	Rule new_rule{ main_symbole, body };
	rules.push_back(new_rule);
}
