#include<iostream>
#include <iostream>
#include <fstream>
#include<string>
#include <regex>
#include "Grammar.hpp"
#include<sstream>
#include<vector>

using namespace std;

bool parse_commande_line_arguments(int argc, char* argv[]);
bool parse_grammar_file();
bool create_earley_table();

string last_error;
ofstream ast_file;
ifstream grammar_file, string_file;
Grammar grammar;
vector<string> input;
EarleyTable table;

int main(int argc, char* argv[])
{
	if (!parse_commande_line_arguments(argc, argv)) {
		cout << last_error << endl;
		return 0;
	}

	if (!parse_grammar_file()) {
		cout << last_error << endl;
		return 0;
	}

	if (!create_earley_table()) {
		cout << last_error << endl;
		return 0;
	}

	// Test if input string recognized or not
	if (table.status())
		cout << "\nSUCCESS !!!!!!!!\n" << endl;
	else
		cout << "\nFAIL !!!!!!!!\n" << endl;

	// Closing the files
	ast_file.close();
	grammar_file.close();
	string_file.close();
	return 0;
}

bool parse_commande_line_arguments(int argc, char* argv[]) 
{
	// The number of arguments should be 2
	if (argc != 3) {
		last_error = "parse_commande_line_arguments : number of argument should be 2";
		return false;
	}

	// Open the files
	grammar_file.open(argv[1]);
	string_file.open(argv[2]);
	ast_file.open("ast.txt", ios::trunc);

	// Test if the file are opened
	if (!grammar_file.is_open()) {
		last_error = "parse_commande_line_arguments : can't open grammar_file";
		return false;
	}

	if (!string_file.is_open()) {
		last_error = "parse_commande_line_arguments : can't open string_file";
		return false;
	}

	if (!ast_file.is_open()) {
		last_error = "parse_commande_line_arguments : can't open ast_file";
		return false;
	}
	return true;
}

bool parse_grammar_file()
{
	// Read the grammar file in a buffer
	string buffer, line;
	while (getline(grammar_file, line))
		buffer += " " + line;

	// Split the symboles of the buffer
	string buf;
	stringstream ss(buffer);
	vector<string> v;
	while (ss >> buf) {
		v.push_back("");
		for (int i = 0; i < buf.size(); ++i) {
			char c = buf[i];
			if (c == ':' || c == ';' || c == '|') {
				if (i != 0)
					v.push_back("");
				v.back() += c;
				v.push_back("");
			}
			else
				v.back() += c;
		}
	}

	// remove empty string from vector
	v.erase(std::remove(v.begin(), v.end(), ""), v.end());

	// if v is empty then we want to parse the empty string
	if (v.size() == 0)
		v.push_back("");
	
	int selector = 0; // 0 : start_symbole,		1 : ':',		 2 : body,		 3 : '|'	4 : ';'
	Rule rule;
	int status;
	for (int i = 0; i < v.size(); ++i) {
		switch (selector)
		{
		case 0:
			if (v[i] == ":" || v[i] == ";" || v[i] == "|") {
				last_error = "parse_grammar_file : Format File Error (0001)";
				return false;
			}
			if (!rule.set_main_symbole(v[i])) {
				last_error = "parse_grammar_file : Format File Error (0002)";
				return false;
			}
			selector = 1;
			break;
		case 1:
			if (v[i] != ":") {
				last_error = "parse_grammar_file : Format File Error (0003)";
				return false;
			}
			selector = 2;
			break;
		case 2:
			if (v[i] == ":") {
				last_error = "parse_grammar_file : Format File Error (0004)";
				return false;
			}
			
		
			// return 0 : nullable symbole terminal
			// return 1 : encounter'|' with empty body
			// return 2 : normale case
			status = rule.push_back_symbole_to_body(v[i]);
			if (status == 0)
				grammar.add_nullable_symbole_if_not_present(rule.get_main_symbole());
			else if (status == 1) {
				last_error = "parse_grammar_file : Format File Error (0005)";
				return false;
			}
				
			if (v[i] == "|") {
				i--;
				selector = 3;
			}
			else if (v[i] == ";") {
				i--;
				selector = 4;
			}
			break;
		case 3:
			// we know a this point that v[i] = "|"
			selector = 2;
			// add the rule to grammar
			grammar.add_rule_if_not_present(rule);
			// clear only body variable
			rule.clear_body();
			break;
		case 4:
			// we know a this point that v[i] = ";"
			selector = 0;
			// add the rule to grammar
			grammar.add_rule_if_not_present(rule);
			// clear rule variable
			rule.clear_rule();
			break;
		default:
			last_error = "parse_grammar_file : Can't happen !";
			return false;
			break;
		}
	}

	// Complete the nullable symbole list
	grammar.get_all_nullable_symboles();

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_nullable_symboles();

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_all_rules();
	return true;
}

bool create_earley_table()
{
	// Read the file in a buffer
	string buffer, line;
	while (getline(string_file, line))
		buffer += " " + line;

	// Split the symboles of the buffer
	string buf;
	stringstream ss(buffer);
	vector<string> v;
	while (ss >> buf)
		v.push_back(buf);

	// Parse the buffer and in an earley table
	table = grammar.parse_string(v);

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_terminal_symboles();

	// FOR DEBUG ONLY : comment it after work finish
	table.print_table();

	return true;
}
