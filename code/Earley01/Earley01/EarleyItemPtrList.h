#pragma once

#include "EarleyItemPtr.h"
#include <vector>
class EarleyItemPtrList
{
private:
	std::vector<EarleyItemPtr> list;

public:
	EarleyItemPtrList();
	void add_item_ptr_if_not_present(EarleyItemPtr item_ptr);
	void add_item_ptr_list(EarleyItemPtrList ptr_list);
};

