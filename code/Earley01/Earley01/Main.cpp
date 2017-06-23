#include<iostream>
//#include <fstream>
#include<string>
#include <regex>
#include "Grammar.h"
#include "Tree.h"
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
EarleyTable* table_ptr;

int main(int argc, char* argv[])
{
	if (!parse_commande_line_arguments(argc, argv)) {
		cout << last_error << endl;
		return 1;
	}

	if (!parse_grammar_file()) {
		cout << last_error << endl;
		return 2;
	}

	if (!create_earley_table()) {
		cout << last_error << endl;
		return 3;
	}

	//// Test if input string recognized or not
	if (table_ptr->status()) {
		// create SPPF Representation
		Tree sppf = table_ptr->generate_sppf_structure();
		// print the representation
		sppf.print_tree_in_dot_format(ast_file);
		// Closing the files
		ast_file.close();
		// Execute dot commande
		system("dot -Tpdf ast.txt -o ast.pdf");
		// open image
		system("ast.pdf");
	}
		
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
		// Open the files
		grammar_file.open("grammar.txt");
		string_file.open("string.txt");
		ast_file.open("ast.txt", ios::trunc);
	}
	else {
		// Open the files
		grammar_file.open(argv[1]);
		string_file.open(argv[2]);
		ast_file.open("ast.txt", ios::trunc);
	}

	

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
	vector<string> vv;
	while (ss >> buf) {
		vv.push_back("");
		for (int i = 0; i < buf.size(); ++i) {
			char c = buf[i];
			if (c == ':' || c == ';' || c == '|') {
				if (i != 0)
					vv.push_back("");
				vv.back() += c;
				vv.push_back("");
			}
			else
				vv.back() += c;
		}
	}

	// remove empty string from vector
	vv.erase(std::remove(vv.begin(), vv.end(), ""), vv.end());

	// if v is empty then error
	if (vv.size() == 0) {
		last_error = "parse_grammar_file : empty grammar file.";
		return false;
	}

	// read terminal symbole
	if (vv[0] != "%token") {
		last_error = "parse_grammar_file : the file must begin with %token x y z;";
		return false;
	}

	int i;
	for (i = 1; vv[i] != ";"; i++) {
		if (vv[i] == "|" || vv[i] == ":") {
			last_error = "parse_grammar_file : the file must begin with %token x y z;";
			return false;
		}
		grammar.add_terminal_symbole_if_not_present(vv[i]);
	}

	vector<string> v(vv.begin() + i + 1, vv.end());

	if (i == 1) {
		last_error = "parse_grammar_file : the file must begin with %token x y z;";
		return false;
	}

	// rule parsing
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
				last_error = "parse_grammar_file : Format File Error (0003) : " + to_string(i);
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
	grammar.compute_nullable_symbole_list();

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_nullable_symbole_list();

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_rule_list();

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
	table_ptr = grammar.create_earley_table_from_input(v);

	// FOR DEBUG ONLY : comment it after work finish
	grammar.print_terminal_symbole_list();

	// FOR DEBUG ONLY : comment it after work finish
	table_ptr->print_table();

	return true;
}