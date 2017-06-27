
#include <iostream>
#include <algorithm>
#include "Grammar.hpp"
#include "EarleyTable.hpp"
#include "EarleyItem.hpp"
#include "Rule.hpp"


using namespace std; 


std::string EarleyTable::get_input_symbol(int symbole_index)
{
	return input_symbole_list[symbole_index];
}

Grammar & EarleyTable::get_grammar()
{
	return grammar;
}

void EarleyTable::compute_earley_table()
{
	// Put start item(s) in E(0)
	for (Rule& r : grammar.get_rule_list()) {
		if (r.get_main_symbole() == grammar.get_start_symbole()) {
			EarleyItem item{ &r, 0, 0 };
			table[0].add_item_if_not_present(item);
		}
	}

	// Populate the reste of E(i)
	for (int i = 0; i < table.size(); ++i) {
		if (i != 0)
			table[i].initialize(); // initialization

		table[i].complete(); // magical_prediction -> prediction -> completion
		table[i].resolve_magical_prediction_reduction_ptr(); // resolve magical_prediction reduction pointer
	}
		
		
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

Tree EarleyTable::generate_sppf_structure()
{
	Tree sppf{ *this };
	sppf.parse_earley_table();
	return sppf;
}

ItemCategory EarleyTable::get_category(EarleyItem * item)
{
	if (item->is_symbole_before_position_is_null()) {
		ItemCategory category{ 1, "", "", "" };
		return category;
	}

	else if (item->is_symbole_before_two_position_is_null()) {
		if (get_grammar().is_terminal_symbole(item->precedent_symbole())) {
			ItemCategory category{ 2, item->precedent_symbole(), "", "" };
			return category;
		}
		else {
			ItemCategory category{ 3, "", item->precedent_symbole(), "" };
			return category;
		}
	}
	else {
		if (get_grammar().is_terminal_symbole(item->precedent_symbole())) {
			ItemCategory category{ 4, item->precedent_symbole(), "", item->get_alpha_prim() };
			return category;
		}
		else {
			ItemCategory category{ 5, "", item->precedent_symbole(), item->get_alpha_prim() };
			return category;
		}
	}
}

bool EarleyTable::status()
{
	string start_symbole = table[0].front().get_rule()->get_main_symbole();
	for (EarleyItem item : table.back().get_set())
		if (item.get_rule()->get_main_symbole() == start_symbole
			&&
			item.get_position() == item.get_rule()->get_body().size()
			&&
			item.get_item_start() == 0)
			return true;

	return false;
}

EarleySet & EarleyTable::front()
{
	return table.front();
}

EarleySet & EarleyTable::back()
{
	return table.back();
}

EarleySet& EarleyTable::get_set(int set_number)
{
	return table[set_number];
}

int EarleyTable::size()
{
	return table.size();
}



