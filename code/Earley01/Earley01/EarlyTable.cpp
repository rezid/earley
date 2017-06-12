#include "EarlyTable.h"
#include "EarleyItem.h"
#include <iostream>
#include <algorithm>

using namespace std; 

EarlyTable::EarlyTable(int string_length)
{
	table.resize(size);
	this->size = string_length + 1;
}

void EarlyTable::add_item_to_set_if_not_present(int set_number, EarleyItem * early_item)
{
	// test if the set number is correct
	if (set_number < 0 || set_number >= size) {
		cout << "EarlyTable::add_item_to_set : set_number not valid";
		return;
	}

	// test if the item is already present, if not add it
	if (std::find(table[set_number].begin(), table[set_number].end(), early_item) == table[set_number].end())
		table[set_number].push_back(early_item);
}

void EarlyTable::print_table()
{
	int i = 0;
	for (auto set : table) {
		cout << "=== " << i << "===\n";
		for (auto item_ptr : set)
			item_ptr->print_item();
		cout << "\n";
	}
	cout << endl;
}

bool EarlyTable::status()
{
	return false;
}
