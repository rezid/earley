#include "EarleyItemPtrList.h"

EarleyItemPtrList::EarleyItemPtrList()
{
}

void EarleyItemPtrList::add_item_ptr_if_not_present(EarleyItemPtr item_ptr)
{
	for (EarleyItemPtr item_ptr1 : list)
		if (item_ptr1 == item_ptr)
			return;

	list.push_back(item_ptr);
}

void EarleyItemPtrList::add_item_ptr_list(EarleyItemPtrList ptr_list)
{
	for (EarleyItemPtr item_ptr : ptr_list.list)
		add_item_ptr_if_not_present(item_ptr);
}
