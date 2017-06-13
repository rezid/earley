#include "Grammar.h"
#include <iostream>
#include "EarleyItem.h"

using namespace std;

Grammar::Grammar(string start_symbole)
{
	this->start_symbole = start_symbole;
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

EarleyTable Grammar::parse_string(string s)
{
	
	// Create an empty table
	EarleyTable table{ static_cast<int>(s.size()) };

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
			else if (is_terminal(next_symbole)) scan(string{ s[i] }, next_symbole, table.get_set(i + 1), table.get_set(i).get_item(j)); // Lecture
			else predict(table.get_set(i), i, next_symbole); // Prediction
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

void Grammar::predict(EarleySet& set, int set_indice, string symbole)
{
	// access by reference to the set
	for (Rule& r : rules)
		if (r.get_main_symbole() == symbole) {
			EarleyItem item{ &r, 0, set_indice };
			set.add_item_if_not_present(item);
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

void Grammar::add_rule(string main_symbole, vector<string> body)
{
	// Create a new rule and add it to the grammar
	Rule new_rule{ main_symbole, body };
	rules.push_back(new_rule);
}
