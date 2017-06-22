#pragma once

#include "EarleyItemPtr.h"
#include <list>
#include <string>

class EarleyItemPtrList
{
private:
	std::list<EarleyItemPtr> list;

public:
	EarleyItemPtrList();
	void add_item_ptr_if_not_present(EarleyItemPtr item_ptr);
	void add_item_ptr_list(EarleyItemPtrList ptr_list);
	void print_ptr_list(std::string name);
};

