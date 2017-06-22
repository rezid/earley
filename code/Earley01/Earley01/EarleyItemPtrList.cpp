#include "EarleyItemPtrList.h"
#include <iostream>
#include "EarleyItem.h"
#include "Rule.h"

using namespace std;

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

void EarleyItemPtrList::print_ptr_list(string name)
{
	if (list.size() == 0)
		return;

	cout << name << ": ";
	for (EarleyItemPtr& item_ptr : list) {
		cout << "[" << item_ptr.get_name() << ", ";
		item_ptr.get_item_ptr()->print_item_without_pointer();
		cout << "] ";
	}

	cout << endl;
}
