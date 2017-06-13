#include<iostream>
#include <iostream>
#include <fstream>
#include<string>
#include <regex>
#include "Grammar.h"
#include<sstream>

using namespace std;

bool parse_commande_line_arguments(int argc, char* argv[]);
bool parse_grammar_file();
bool create_earley_table();

string last_error;
ofstream ast_file;
ifstream grammar_file, string_file;
Grammar grammar("S");

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
	string line;
	regex token{ "^%token (.+)" };
	std::smatch m;

	getline(grammar_file, line);
	regex_match(line, m, token);

	// Test if error in %token
	if (m[0] == "") {
		last_error = "parse_grammar_file : %token format error or not found";
		return false;
	}

	// Split the match
	string buf; 
	stringstream ss(m[1]);
	while (ss >> buf)
		grammar.add_terminal_symbole(buf);


	// FOR DEBUG ONLY : comment it after work finish
	//grammar.print_terminal_symboles();

	// Parse the rules
	regex rule{ "^(\\S+) : (.+)" };
	while (getline(grammar_file, line))
	{
		regex_match(line, m, rule);

		// Split the match
		string buf;
		stringstream ss(m[2]);
		vector<string> l;
		while (ss >> buf)
			l.push_back(buf);

		// add the rule to grammar
		grammar.add_rule(m[1], l);
		
	}
	
	// FOR DEBUG ONLY : comment it after work finish
	//grammar.print_all_rules();

	return true;
}

bool create_earley_table()
{
	// Read all the string file in a buffer
	string buffer, line;
	while (getline(string_file, line))
		buffer += line;

	// Parse the buffer and create an earley table
	EarleyTable table = grammar.parse_string(buffer);

	// FOR DEBUG ONLY : comment it after work finish
	table.print_table();

	return true;
}