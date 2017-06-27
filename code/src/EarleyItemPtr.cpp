#include "EarleyItemPtr.hpp"
#include "EarleyItem.hpp"

EarleyItemPtr::EarleyItemPtr(int name, EarleyItem * item_ptr)
{
	this->name = name;
	this->item_ptr = item_ptr;
}

bool EarleyItemPtr::operator==(const EarleyItemPtr& item) const
{
	if (name == item.name && (*item_ptr) == *(item.item_ptr))
		return true;

	return false;
}

int EarleyItemPtr::get_name()
{
	return name;
}

EarleyItem * EarleyItemPtr::get_item_ptr()
{
	return item_ptr;
}
