#pragma once

#include<string>
#include<list>

#include "Node.h"

class EarleyTable;
class EarleyItem;


class Tree
{
private:
	EarleyTable& table;
	std::list<Node> node_list;
	Node epsilon{ "epsilon", 0, 0 };

public:
	Tree(EarleyTable& table);


	void parse_earley_table();
	void build_tree(Node* node, EarleyItem* item, int i);
	Node* add_node_if_not_present(Node* node);
	Node& get_epsilon();

	void print_tree();
	void print_tree_in_dot_format(std::ostream& dot_file);
	
};

