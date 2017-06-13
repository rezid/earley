#pragma once

#include<string>
#include<vector>

class Rule
{
private:
	std::string main_symbole;
	std::vector<std::string> body;
	bool main_symbole_is_set;

public:
	Rule();
	Rule(std::string main_symbole, std::vector<std::string> body);
	void print_rule();
	void print_Earley_rule(int position, int item_start);
	std::string get_main_symbole();
	std::string get_symbole(int symbole_offset);
	bool set_main_symbole(std::string main_symbole);
	void set_body(std::vector<std::string> body);
	std::vector<std::string> get_body();
	bool push_back_symbole_to_body(std::string symbole);
	void clear_rule();
	bool operator== (const Rule& rule) const;
};

