#pragma once

class EarleyItem;

class EarleyItemPtr
{
private:
	int name;
	EarleyItem* item_ptr;
public:
	EarleyItemPtr(int name, EarleyItem* item_ptr);
	bool operator== (const EarleyItemPtr& item) const;

	int get_name();
	EarleyItem* get_item_ptr();
};

