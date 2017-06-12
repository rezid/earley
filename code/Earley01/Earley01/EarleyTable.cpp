#include "EarleyTable.h"
#include "EarleyItem.h"
#include <iostream>
#include <algorithm>

using namespace std; 

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
	// TO DO
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
