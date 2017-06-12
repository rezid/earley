#pragma once

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
	void print_item();
};

