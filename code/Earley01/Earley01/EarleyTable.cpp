
#include <iostream>
#include <algorithm>
#include "Grammar.h"
#include "EarleyTable.h"
#include "EarleyItem.h"
#include "Rule.h"

using namespace std; 


std::string EarleyTable::get_input_symbol(int symbole_index)
{
	return input_symbole_list[symbole_index];
}

Grammar & EarleyTable::get_grammar()
{
	return grammar;
}

void EarleyTable::compute_earley_table()
{
	// Put start item(s) in E(0)
	for (Rule& r : grammar.get_rule_list()) {
		if (r.get_main_symbole() == grammar.get_start_symbole()) {
			EarleyItem item{ &r, 0, 0 };
			table[0].add_item_if_not_present(item);
		}
	}

	// Populate the reste of E(i)
	for (int i = 0; i < table.size(); ++i) {
		if (i != 0)
			table[i].initialize(); // initialization

		table[i].complete(); // magical_prediction -> prediction -> completion
		table[i].resolve_magical_prediction_reduction_ptr(); // resolve magical_prediction reduction pointer
	}
		
		
}

void EarleyTable::add_item_to_set_if_not_present(int set_number, EarleyItem item)
{
	table[set_number].add_item_if_not_present(item);
}

void EarleyTable::print_table()
{
	int i = 0;
	for (auto set : table) {
		cout << "=== " << i << " ===\n";
		set.print_set();
		++i;
	}
	cout << endl;
}

bool EarleyTable::status()
{
	string start_symbole = table[0].front().get_rule()->get_main_symbole();
	int size = table.back().size();
	for (EarleyItem item : table.back().get_set())
		if (item.get_rule()->get_main_symbole() == start_symbole
			&&
			item.get_position() == item.get_rule()->get_body().size()
			&&
			item.get_item_start() == 0)
			return true;

	return false;
}

EarleySet& EarleyTable::get_set(int set_number)
{
	return table[set_number];
}

int EarleyTable::size()
{
	return table.size();
}



