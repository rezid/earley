#include "EarleyItem.hpp"
#include "Rule.hpp"

using namespace std;

EarleyItem::EarleyItem(Rule* rule_ptr, int position, int item_start)
{
	this->rule_ptr = rule_ptr;
	this->position = position;
	this->item_start = item_start;
}

string EarleyItem::next_symbole()
{
	return rule_ptr->get_symbole(position);
}

void EarleyItem::print_item()
{
	rule_ptr->print_Earley_rule(position, item_start);
}

bool EarleyItem::operator==(const EarleyItem & item) const
{
	if (rule_ptr == item.rule_ptr && position == item.position && item_start == item.item_start)
		return true;

	return false;
}

EarleyItem EarleyItem::next_item()
{
	EarleyItem item{ rule_ptr, position + 1, item_start };
	return item;
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
