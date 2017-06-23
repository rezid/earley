#pragma once

#include<string>
#include<list>


class Node
{
private:
	std::string first;
	int second;
	int third;

	std::list<std::list<Node*> > families;

	bool root = false;
	bool marked = false;

public:
	Node(std::string first, int second, int third);

	bool has_family(Node* v);
	bool has_family(Node* w, Node* v);

	void add_family(Node* v);
	void add_family(Node* w, Node* v);

	bool operator== (const Node& node) const;

	void set_root(bool b) { root = b; }

	bool is_root() { return root; }

	std::string name() { return first + ", " + std::to_string(second) + ", " + std::to_string(third); }

	bool is_marked() { return marked; }

	void mark() { marked = true; }

	void print_tree();

	void print_tree_in_dot_format(std::ostream& dot_file, int i = 0);


};

