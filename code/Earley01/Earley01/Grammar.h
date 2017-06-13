#pragma once

#include "Rule.h"
#include "EarleyTable.h"
#include "EarleySet.h"


class Grammar
{
private:
	std::string start_symbole;
	std::vector<std::string> terminals;
	std::vector<Rule> rules;

public:
	Grammar();
	void set_start_symbole(std::string start_symbole);
	void add_rule_if_not_present(Rule rule);
	void add_terminal_symbole(std::string name);
	void print_terminal_symboles();
	void print_all_rules();
	EarleyTable parse_string(std::vector<std::string> symboles_input);
	bool is_terminal(std::string symbole);
	void predict(EarleySet& item_set, int set_indice, std::string symbole);
	void scan(std::string input, std::string symbole, EarleySet& next_item_set, EarleyItem item);
	void complete(EarleySet& curent_set, EarleySet& old_set, std::string start_symbole);
};

