#pragma once

#include <string>

class Rule;

// Exemple of an Earley item : S : •S + F (2)
class EarleyItem
{
private:
	Rule* rule_ptr;      // S : S + F
	int position;        // the dot: •
	int item_start;      // the numnber between parenthesis: (2)

public:
	EarleyItem(Rule* rule_ptr, int position, int item_start);
	std::string next_symbole();
	void print_item();
	bool operator== (const EarleyItem& item) const;
	EarleyItem next_item();
	int get_item_start();
	Rule* get_rule();
};

 