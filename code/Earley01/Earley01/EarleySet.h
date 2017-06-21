#pragma once

#include "EarleyItem.h"
#include <vector>
#include <string>

class EarleyTable;

class EarleySet
{
private:
	std::vector<EarleyItem> set;
	
	int index;
	EarleyTable& earley_table;

	void magical_prediction(EarleyItem current_item);
	void prediction(EarleyItem current_item);
	void completion(EarleyItem current_item);

public:
	EarleySet* precedent_set;
	EarleySet(EarleySet* precedent_set, EarleyTable& earley_table);

	void set_precedent_set(EarleySet* precedent_set);

	void add_item_if_not_present(EarleyItem item);

	EarleyItem get_item(int i);

	int size();

	void print_set();

	void initialize();
	void complete();
	void resolve_magical_prediction_reduction_ptr();
};