#include<iostream>
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

bool parse_commande_line_arguments(int argc, char* argv[]);
bool parse_grammar_file();

string last_error;
ofstream ast_file;
ifstream grammar_file, string_file;

int main(int argc, char* argv[])
{
	if (!parse_commande_line_arguments(argc, argv))
		cout << last_error << endl;


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
