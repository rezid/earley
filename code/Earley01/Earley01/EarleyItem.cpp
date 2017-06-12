#include "EarleyItem.h"

EarleyItem::EarleyItem(Rule* rule_ptr, int position, int item_start)
{
	this->rule_ptr = rule_ptr;
	this->position = position;
	this->item_start = item_start;
}
