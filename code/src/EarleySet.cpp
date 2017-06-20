#include "EarleySet.hpp"
#include <iostream>

using namespace std;

EarleySet::EarleySet()
{
}

void EarleySet::add_item_if_not_present(EarleyItem item1)
{
	for (EarleyItem item : set)
		if (item == item1)
			return;

	set.push_back(item1);
}

void EarleySet::print_set()
{
	for (auto item : set)
		item.print_item();
	cout << "\n";
}

int EarleySet::size()
{
	return set.size();
}

EarleyItem& EarleySet::get_item(int i)
{
	return set[i];
}
