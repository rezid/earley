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
};

