#pragma once

#include <string>
#include "EarleyItemPtrList.h"
#include "EarleyItemPtr.h"

class Rule;

// Exemple of an Earley item : S : •S + F (2)
class EarleyItem
{
private:
	Rule* rule_ptr;      // S : S + F
	int position;        // the dot: •
	int item_start;      // the number between parenthesis: (2)
	EarleyItemPtrList reduction_ptr_list; 
	EarleyItemPtrList predecessor_ptr_list;
	bool symbole_before_position_is_null;
	bool from_magical_reduction;
	
public:
	EarleyItem(Rule* rule_ptr, int position, int item_start, bool is_from_magical_reduction = false);
	std::string next_symbole();
	std::string precedent_symbole();
	void print_item();
	bool operator== (const EarleyItem& item) const;
	EarleyItem* next_item(bool is_from_magical_reduction = false);
	int get_item_start();
	int get_position();
	Rule* get_rule();
	void add_reduction_ptr(EarleyItemPtr reduction_ptr);
	void add_predecessor_ptr(EarleyItemPtr precedessor_ptr);
	EarleyItemPtrList& get_reduction_ptr_list();
	EarleyItemPtrList& get_predecessor_ptr_list();
	bool is_symbole_before_position_is_null();
	bool is_symbole_before_position_is_not_null();
	bool is_complete();
	bool is_from_magical_reduction();
	void set_from_magical_reduction(bool from_magical_reduction);
};

 