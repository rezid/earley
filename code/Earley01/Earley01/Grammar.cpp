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
	// search if a rule exist with the main symbole
	for (Rule& r : rules) {
		if (r.get_main_symbole() == main_symbole) {
			r.add_a_body(body);
			return;
		}
	}

	// if not, create a new rule and add it to the grammar
	Rule new_rule{ main_symbole };
	new_rule.add_a_body(body);
	rules.push_back(new_rule);
}
