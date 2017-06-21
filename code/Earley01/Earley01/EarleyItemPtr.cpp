#include "EarleyItemPtr.h"
#include "EarleyItem.h"

EarleyItemPtr::EarleyItemPtr(int name, EarleyItem * item_ptr)
{
	this->name = name;
	this->item_ptr = item_ptr;
}

bool EarleyItemPtr::operator==(const EarleyItemPtr& item) const
{
	if (name == item.name && *item_ptr == *(item.item_ptr))
		return true;

	return false;
}
