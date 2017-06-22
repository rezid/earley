#pragma once

#include "EarleyItem.h"
#include <list>
#include <string>

class EarleyTable;

class EarleySet
{
private:
	std::list<EarleyItem> set;
	
	int index;
	EarleyTable& earley_table;

	void magical_prediction(EarleyItem& current_item);
	void prediction(EarleyItem current_item);
	void completion(EarleyItem& current_item);

public:
	EarleySet* precedent_set;
	EarleySet(EarleySet* precedent_set, EarleyTable& earley_table);

	void set_precedent_set(EarleySet* precedent_set);

	std::list<EarleyItem>& get_set();

	void add_item_if_not_present(EarleyItem& item);

	EarleyItem& front();

	int size();

	void print_set();

	void initialize();
	void complete();
	void resolve_magical_prediction_reduction_ptr();
};