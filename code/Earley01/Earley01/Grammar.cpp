#include "Grammar.h"
#include <iostream>
#include "EarleyItem.h"
#include "EarleyTable.h"

using namespace std;

Grammar::Grammar()
{
}

void Grammar::set_start_symbole(std::string start_symbole)
{
	this->start_symbole = start_symbole;
}

void Grammar::add_terminal_symbole_if_not_present(std::string terminal_symbole_name)
{
	for (auto s : terminal_symbole_list)
		if (s == terminal_symbole_name)
			return;
	terminal_symbole_list.push_back(terminal_symbole_name);
}

void Grammar::set_terminal_symbole_list(std::vector<std::string> terminal_symbole_list)
{
	this->terminal_symbole_list = terminal_symbole_list;
}

void Grammar::print_terminal_symbole_list()
{
	cout << "\nThe "<< terminal_symbole_list.size() <<" terminal symboles are: ";
	for (auto t : terminal_symbole_list)
		cout << t << " ";

	cout << "\n" << endl;
}

void Grammar::print_rule_list()
{
	cout << "\n-----------GRAMMAR RULES-----------\n";
	for (auto r : rule_list)
		r.print_rule();
	cout << "-----------------------------------\n" << endl;
}

EarleyTable* Grammar::create_earley_table_from_input(std::vector<std::string>& input_symbole_list) {
	// Create an empty table
	EarleyTable* table_ptr = new EarleyTable{ *this, input_symbole_list };

	// Compute the earley table
	table_ptr->compute_earley_table();

	// return the earley table
	return table_ptr;
}

bool Grammar::is_terminal_symbole(std::string symbole)
{
	for (string s : terminal_symbole_list)
		if (s == symbole)
			return true;

	return false;
}

bool Grammar::is_not_terminal_symbole(std::string symbole)
{
	return !is_terminal_symbole(symbole);
}

void Grammar::add_nullable_symbole_if_not_present(std::string symbole)
{
	for (auto s : nullable_symbole_list)
		if (s == symbole)
			return;

	nullable_symbole_list.push_back(symbole);
}

std::vector<Rule>& Grammar::get_rule_list()
{
	return rule_list;
}

std::string & Grammar::get_start_symbole()
{
	return start_symbole;
}

void Grammar::compute_nullable_symbole_list()
{
	if (nullable_symbole_list.size() == 0)
		return;

	for (int i = 0; i < rule_list.size(); ++i)
		for (auto rule : rule_list) {
			if (is_nullable_symbole(rule.get_main_symbole()))
				continue;
			for (string s : rule.get_body())
				if (!is_nullable_symbole(s))
					goto end;
			add_nullable_symbole_if_not_present(rule.get_main_symbole());
		end:;
		}
}

bool Grammar::is_nullable_symbole(std::string symbole_name)
{
	for (auto s : nullable_symbole_list)
		if (s == symbole_name)
			return true;

	return false;
}

void Grammar::print_nullable_symbole_list()
{
	cout << "\nThe nullable symboles are: ";
	for (auto s : nullable_symbole_list)
		cout << s << " ";
	cout << "\n" << endl;
}

void Grammar::add_rule_if_not_present(Rule rule)
{
	// If first rule in grammar, set the start symbole to be main_symbole
	if (rule_list.size() == 0)
		set_start_symbole(rule.get_main_symbole());

	// Test if a same rule already exist in grammar, if not add it to the grammar
	for (Rule r : rule_list)
		if (r == rule)
			return;
	
	rule_list.push_back(rule);
}

