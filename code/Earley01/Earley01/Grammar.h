#pragma once

#include "Rule.h"
#include "EarleySet.h"
#include "EarleyTable.h"

class Grammar
{
private:
	std::string start_symbole;
	std::vector<std::string> terminal_symbole_list;
	std::vector<Rule> rule_list;
	std::vector<std::string> nullable_symbole_list;

public:
	Grammar();

	void set_start_symbole(std::string start_symbole);
	void set_terminal_symbole_list(std::vector<std::string> terminal_symbole_list);
	
	void add_rule_if_not_present(Rule rule);
	void add_terminal_symbole_if_not_present(std::string terminal_symbole_name);
	void add_nullable_symbole_if_not_present(std::string symbole_name);

	std::vector<Rule>& get_rule_list();
	std::string& get_start_symbole();

	void print_terminal_symbole_list();
	void print_rule_list();
	void print_nullable_symbole_list();

	
	bool is_terminal_symbole(std::string symbole_name);
	bool is_not_terminal_symbole(std::string symbole_name);
	bool is_nullable_symbole(std::string symbole_name);

	void compute_nullable_symbole_list();
	
	EarleyTable* create_earley_table_from_input(std::vector<std::string>& symbole_input_list);

};

