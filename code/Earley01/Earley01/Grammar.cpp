#include "Grammar.h"
#include<iostream>

using namespace std;

Grammar::Grammar()
{
}

void Grammar::add_a_rule(string main_symbole, list<string> body)
{
	// search if a rule exist with the main symbole
	for (Rule r : rules) {
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
