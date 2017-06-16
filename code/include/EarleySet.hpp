#pragma once

#include "EarleyItem.hpp"
#include <vector>

class EarleySet
{
private:
	std::vector<EarleyItem> set;

public:
	EarleySet();
	void add_item_if_not_present(EarleyItem item);
	void print_set();
	
	int size();
	EarleyItem& get_item(int i);
};

