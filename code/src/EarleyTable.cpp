#include "EarleyTable.hpp"
#include "EarleyItem.hpp"
#include "Rule.hpp"
#include <iostream>
#include <algorithm>

using namespace std; 

EarleyTable::EarleyTable()
{
}

EarleyTable::EarleyTable(int input_string_size)
{
	table.resize(input_string_size + 1);
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
	string start_symbole = table[0].get_item(0).get_rule()->get_main_symbole();
	int size = table.back().size();
	for (int i = 0; i < size; ++i)
		if (table.back().get_item(i).get_rule()->get_main_symbole() == start_symbole
			&&
			table.back().get_item(i).get_position() == table.back().get_item(i).get_rule()->get_body().size()
			&&
			table.back().get_item(i).get_item_start() == 0)
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
