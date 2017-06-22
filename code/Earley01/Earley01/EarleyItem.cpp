#include "EarleyItem.h"
#include "Rule.h"
#include<iostream>

using namespace std;

EarleyItem::EarleyItem(Rule* rule_ptr, int position, int item_start, bool from_magical_reduction)
{
	// TODO : position borné

	this->rule_ptr = rule_ptr;
	this->position = position;
	this->item_start = item_start;
	this->from_magical_reduction = from_magical_reduction;


	if (position == 0)
		symbole_before_position_is_null = true;
	else
		symbole_before_position_is_null = false;
}

string EarleyItem::next_symbole()
{
	return rule_ptr->get_symbole(position);
}

std::string EarleyItem::precedent_symbole()
{
	return rule_ptr->get_symbole(position - 1);
}

void EarleyItem::print_item()
{
	rule_ptr->print_Earley_rule(position, item_start); 
	cout << endl;
	reduction_ptr_list.print_ptr_list("reduction");
	predecessor_ptr_list.print_ptr_list("predecessor");
	cout << endl;
}

void EarleyItem::print_item_without_pointer()
{
	rule_ptr->print_Earley_rule(position, item_start);
}

bool EarleyItem::operator==(const EarleyItem & item) const
{
	if (rule_ptr == item.rule_ptr && position == item.position && item_start == item.item_start)
	   return true;

	return false;
}

EarleyItem* EarleyItem::next_item(bool from_magical_reduction)
{
	EarleyItem* item_ptr = new EarleyItem{ rule_ptr, position + 1, item_start };
	item_ptr->symbole_before_position_is_null = false;
	item_ptr->from_magical_reduction = from_magical_reduction;
	return item_ptr;
}

int EarleyItem::get_item_start()
{
	return item_start;
}

int EarleyItem::get_position()
{
	return position;
}

Rule * EarleyItem::get_rule()
{
	return rule_ptr;
}

void EarleyItem::add_reduction_ptr(EarleyItemPtr reduction_ptr)
{
	reduction_ptr_list.add_item_ptr_if_not_present(reduction_ptr);
}

void EarleyItem::add_predecessor_ptr(EarleyItemPtr precedessor_ptr)
{
	predecessor_ptr_list.add_item_ptr_if_not_present(precedessor_ptr);
}

EarleyItemPtrList & EarleyItem::get_reduction_ptr_list()
{
	return reduction_ptr_list;
}

EarleyItemPtrList & EarleyItem::get_predecessor_ptr_list()
{
	return predecessor_ptr_list;
}

bool EarleyItem::is_symbole_before_position_is_null()
{
	return symbole_before_position_is_null;
}

bool EarleyItem::is_symbole_before_position_is_not_null()
{
	return !is_symbole_before_position_is_null();
}

bool EarleyItem::is_complete()
{
	if (rule_ptr->get_body().size() == position)
		return true;

	return false;
}

bool EarleyItem::is_from_magical_reduction()
{
	return from_magical_reduction;
}

void EarleyItem::set_from_magical_reduction(bool from_magical_reduction)
{
	this->from_magical_reduction = from_magical_reduction;
}


