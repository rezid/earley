#pragma once

#include "EarleySet.h"
#include <vector>

class EarleyTable
{
private:
	std::vector<EarleySet> table;

public:
	EarleyTable();
	EarleyTable(int input_string_size);
	void add_item_to_set_if_not_present(int set_number, EarleyItem item);
	void print_table();
	bool status();
	EarleySet& get_set(int set_number);
	int size();
};

