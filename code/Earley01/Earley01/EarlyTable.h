#pragma once

#include<vector>

class EarleyItem;

class EarlyTable
{
private:
	std::vector<std::vector<EarleyItem*> > table;
	int size;

public:
	EarlyTable(int string_length);
	void add_item_to_set_if_not_present(int set_number, EarleyItem* early_item);
	void print_table();
	bool status();
};

