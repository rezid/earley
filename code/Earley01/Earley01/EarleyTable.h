#pragma once

#include "Rule.h"
#include "EarleySet.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Grammar;

class EarleyTable
{
private:
	std::vector<EarleySet> table;
	std::vector<std::string> input_symbole_list;
	Grammar& grammar;

	void add_item_to_set_if_not_present(int set_number, EarleyItem item);
	
	
	int size();

public:
	EarleyTable(Grammar& grammar, std::vector<std::string>& input_symbole_list)
		: grammar(grammar), input_symbole_list(input_symbole_list)
	{
		table.resize(input_symbole_list.size() + 1, EarleySet{ nullptr, *this });

		for (int i = 0; i < input_symbole_list.size() + 1; ++i)
			if (i != 0)
				table[i].set_precedent_set(&(table[i - 1]));
	};

	std::string get_input_symbol(int symbole_index);
	Grammar& get_grammar();
	EarleySet& get_set(int set_number);

	void compute_earley_table();
	bool status();

	void print_table();

	
};

