#include "Rule.h"
#include<iostream>

using namespace std;

Rule::Rule(string start)
{
	this->start = start;
}

void Rule::add_a_body(list<string> body)
{
	bodies.push_back(body);
}

void Rule::print_rule()
{
	for (list<string> l : bodies) {
		cout << start << " : ";

		for (string s : l)
			cout << s << " ";

		cout << endl;
	}
}



