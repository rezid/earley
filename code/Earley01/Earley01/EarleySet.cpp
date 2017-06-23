#include "EarleySet.h"
#include "EarleyTable.h"
#include "EarleyItemPtr.h"
#include "Grammar.h"
#include "Rule.h"
#include <iostream>


using namespace std;


EarleySet::EarleySet(EarleySet* precedent_set, EarleyTable& earley_table)
	: earley_table(earley_table)
{
	this->precedent_set = precedent_set;
	if (precedent_set == nullptr)
		index = 0;
	else
		index = precedent_set->index + 1;
}

void EarleySet::add_item_if_not_present(EarleyItem& item1)
{
	for (EarleyItem& item : set)
		if (item == item1) {
			item.get_predecessor_ptr_list().add_item_ptr_list(item1.get_predecessor_ptr_list());
			item.get_reduction_ptr_list().add_item_ptr_list(item1.get_reduction_ptr_list());
			bool b = item.is_from_magical_reduction() || item1.is_from_magical_reduction();
			item.set_from_magical_reduction(b);
			return;
		}
	set.push_back(item1);
}

EarleyItem & EarleySet::front()
{
	return set.front();
}

void EarleySet::print_set()
{
	for (auto item : set)
		item.print_item();
	cout << "\n";
}

void EarleySet::set_precedent_set(EarleySet * precedent_set)
	
{
	this->precedent_set = precedent_set;

	if (precedent_set == nullptr)
		index = 0;
	else
		index = precedent_set->index + 1;
}

std::list<EarleyItem>& EarleySet::get_set()
{
	return set;
}

int EarleySet::size()
{
	return set.size();
}


void EarleySet::initialize()
{
	// E0 : no initialization
	if (precedent_set == nullptr)
		return;

	// already initialized
	if (set.size() != 0)
		return;

	// initialize using precedent set and add predecessor pointer
	for (EarleyItem& item : precedent_set->set) {

		EarleyItem* new_item = nullptr;
		if (item.get_position() != item.get_rule()->get_body().size())
			if (earley_table.get_grammar().is_terminal_symbole(item.next_symbole())) {
				if (item.next_symbole() == item.get_rule()->get_body().at(item.get_position()))
					new_item = item.next_item(false);
			}
			else
				new_item = item.next_item(false);

			
		if (new_item != nullptr) {
			
			if (item.is_symbole_before_position_is_not_null()) {
				EarleyItemPtr predecessor_ptr{ index - 1, &item };
				new_item->add_predecessor_ptr(predecessor_ptr);
			}
			add_item_if_not_present(*new_item);
		}	
	}
}

void EarleySet::complete()
{
	for (EarleyItem& item : set)
		if (item.is_complete()) {
			completion(item);
		}
		else {
			if (earley_table.get_grammar().is_nullable_symbole(item.next_symbole())) {
				magical_prediction(item);
				prediction(item);
			}
			else if (earley_table.get_grammar().is_not_terminal_symbole(item.next_symbole())) {
				prediction(item);
			}
		}
}

void EarleySet::resolve_magical_prediction_reduction_ptr()
{
	for (EarleyItem& item : set)
		if (item.is_from_magical_reduction()) {
			for (EarleyItem& item1 : set) {
				if (item1.is_complete() &&
					item1.get_rule()->get_main_symbole() == item.precedent_symbole() &&
					item1.get_item_start() == index)
				{
					// add reduction pointer
					EarleyItemPtr reduction_ptr{ index, &item1 };
					item.add_reduction_ptr(reduction_ptr);
				}
			}
			item.set_from_magical_reduction(false);
		}	
}

int EarleySet::get_index()
{
	return index;
}

void EarleySet::prediction(EarleyItem current_item)
{
	for (Rule& r : earley_table.get_grammar().get_rule_list()) {
		if (current_item.get_position() != current_item.get_rule()->get_body().size()) {
			if (current_item.next_symbole() == r.get_main_symbole()) {
				EarleyItem* item_ptr = new EarleyItem{ &r, 0, index, false };
				add_item_if_not_present(*item_ptr);
			}
		}
	}
}

void EarleySet::magical_prediction(EarleyItem& current_item)
{
	// Create next item with is_from_magical_reduction = true
	EarleyItem* item_ptr = nullptr;
	if (current_item.get_position() != current_item.get_rule()->get_body().size())
		if (!earley_table.get_grammar().is_terminal_symbole(current_item.next_symbole()))
			item_ptr = current_item.next_item(true);

	if (item_ptr == nullptr)
		return;

	// Add predecessor pointer in some case
	if (current_item.is_symbole_before_position_is_not_null()) {
		EarleyItemPtr predecessor_ptr{ index, &current_item };
		item_ptr->add_predecessor_ptr(predecessor_ptr);
	}
		
	// add new item to the current set E(i) where i = index
	add_item_if_not_present(*item_ptr);
}

void EarleySet::completion(EarleyItem& current_item)
{
	EarleySet& previous_set = earley_table.get_set(current_item.get_item_start());

	for (EarleyItem& item : previous_set.set)
		if (item.get_position() != item.get_rule()->get_body().size())
			if (item.next_symbole() == current_item.get_rule()->get_main_symbole()) {
				// Create item
				EarleyItem* item_ptr = item.next_item(false);

				// add reduction pointer
				EarleyItemPtr reduction_ptr{ previous_set.index, &current_item };
				item_ptr->add_reduction_ptr(reduction_ptr);

				// Add predecessor pointer in some case
				if (item.is_symbole_before_position_is_not_null()) {
					EarleyItemPtr predecessor_ptr{ previous_set.index, &(item) };
					item_ptr->add_predecessor_ptr(predecessor_ptr);
				}

				// add the new item to the set E(i)
				add_item_if_not_present(*item_ptr);
			}
}