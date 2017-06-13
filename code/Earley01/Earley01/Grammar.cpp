#include "Grammar.h"
#include <iostream>
#include "EarleyItem.h"

using namespace std;

Grammar::Grammar()
{
}

void Grammar::set_start_symbole(std::string start_symbole)
{
	this->start_symbole = start_symbole;
}

void Grammar::add_terminal_symbole(std::string name)
{
	terminals.push_back(name);
}

void Grammar::set_terminals(std::vector<std::string> terminals)
{
	this->terminals = terminals;
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

EarleyTable Grammar::parse_string(std::vector<std::string> symboles_input)
{
	// Create the terminal symboles from the input symboles
	set_terminals(symboles_input);

	// Create an empty table
	EarleyTable table{ static_cast<int>(symboles_input.size()) };

	// Put start item(s) in E(0)
	for (Rule& r : rules) {
		if (r.get_main_symbole() == start_symbole) { 
			EarleyItem item{ &r, 0, 0 };
			table.add_item_to_set_if_not_present(0, item);
		}
	}

	// Populate the reste of E(i)
	for (int i = 0; i < table.size(); ++i)
		for (int j = 0; j < table.get_set(i).size(); ++j) {
			string next_symbole = table.get_set(i).get_item(j).next_symbole();
			if (next_symbole == "") {
				int old_set_indice = table.get_set(i).get_item(j).get_item_start();
				string start_symbole = table.get_set(i).get_item(j).get_rule()->get_main_symbole();
				complete(table.get_set(i), table.get_set(old_set_indice), start_symbole);  // Complétion
			}
			else if (is_terminal(next_symbole) && i != table.size() - 1) scan(symboles_input[i], next_symbole, table.get_set(i + 1), table.get_set(i).get_item(j)); // Lecture
			else predict(table.get_set(i), i, next_symbole, table.get_set(i).get_item(j)); // Prediction
		}

	// return the earley table
	return table;
}

bool Grammar::is_terminal(std::string symbole)
{
	for (string s : terminals)
		if (s == symbole)
			return true;

	return false;
}

void Grammar::predict(EarleySet& set, int set_indice, string symbole, EarleyItem& current_item)
{
	// access by reference to the set
	for (Rule& r : rules)
		if (r.get_main_symbole() == symbole) {
			EarleyItem item{ &r, 0, set_indice };
			set.add_item_if_not_present(item);

			// magical completition for nullable symbole
			if (is_nullable(symbole)) {
				EarleyItem item = current_item.next_item();
				set.add_item_if_not_present(item);
			}

		}	
}

void Grammar::scan(std::string input, std::string symbole, EarleySet & next_item_set, EarleyItem item1)
{
	// Scan failed
	if (input != symbole)
		return;

	// Success scan : add item to the next set
	EarleyItem item = item1.next_item();
	next_item_set.add_item_if_not_present(item);
}

void Grammar::complete(EarleySet & curent_set, EarleySet & old_set, string start_symbole)
{
	for (int i = 0; i < old_set.size(); ++i)
		if (old_set.get_item(i).next_symbole() == start_symbole) {
			EarleyItem item = old_set.get_item(i).next_item();
			curent_set.add_item_if_not_present(item);
		}

}

void Grammar::add_nullable_symbole_if_not_present(std::string symbole)
{
	for (auto s : nullable_symboles)
		if (s == symbole)
			return;

	nullable_symboles.push_back(symbole);
}

void Grammar::get_all_nullable_symboles()
{
	for (int i = 0; i < rules.size(); ++i)
		for (auto rule : rules) {
			if (is_nullable(rule.get_main_symbole()))
				continue;
			for (string s : rule.get_body())
				if (!is_nullable(s))
					continue;
			add_nullable_symbole_if_not_present(rule.get_main_symbole());
		}
}

bool Grammar::is_nullable(std::string symbole)
{
	for (auto s : nullable_symboles)
		if (s == symbole)
			return true;

	return false;
}

void Grammar::print_nullable_symboles()
{
	cout << "\nThe nullable symboles are: ";
	for (auto s : nullable_symboles)
		cout << s << " ";
	cout << "\n" << endl;
}

void Grammar::add_rule_if_not_present(Rule rule)
{
	// If first rule in grammar, set the start symbole to be main_symbole
	if (rules.size() == 0)
		set_start_symbole(rule.get_main_symbole());

	// Test if a same rule already exist in grammar, if not add it to the grammar
	for (Rule r : rules)
		if (r == rule)
			return;
	
	rules.push_back(rule);
}

