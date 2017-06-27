#include "Node.hpp"
#include <iostream>


using namespace std;


Node::Node(std::string first, int second, int third)
{
	this->first = first;
	this->second = second;
	this->third = third;
}

bool Node::has_family(Node * v)
{
	for (std::list<Node*> family : families)
		if (family.size() == 1 && (*(family.front()) == *v))
			return true;
	return false;
}

bool Node::has_family(Node * w, Node * v)
{
	for (std::list<Node*> family : families)
		if (family.size() == 2 && (*(family.front()) == *w) && (*(family.back()) == *v))
			return true;
	return false;
}

void Node::add_family(Node * v)
{
	list<Node*> * family_ptr = new list<Node*>();
	family_ptr->push_back(v);
	families.push_back(*family_ptr);
}

void Node::add_family(Node * w, Node * v)
{
	list<Node*> * family_ptr = new list<Node*>();
	family_ptr->push_back(w);
	family_ptr->push_back(v);
	families.push_back(*family_ptr);
}

bool Node::operator==(const Node & node) const
{
	if (first == node.first && second == node.second && third == node.third)
		return true;
	return false;
}

void Node::print_tree()
{
	if (is_marked())
		return;

	mark();

	cout << name() << " --> ";
	for (auto& family : families) { 
		cout << "{ ";
		for (auto& node : family) {
			cout << node->name() << " ";
		}
		cout << "}  ";
	}
	cout << endl;

	for (auto& family : families) {
		for (auto& node : family) {
			node->print_tree();
		}
	
	}


}

void Node::print_tree_in_dot_format(ostream & dot_file, int i)
{
	
	if (is_marked())
		return;

	mark();

	for (auto& family : families) {
		if (families.size() >= 2) {
			string s = std::to_string(++i);
			dot_file << "\"" << s << "\"[shape=circle,width=.1,style=filled,label=\"\"];" << "\n";
			dot_file << "\"" << name() << "\"" << " -> " << "\"" << s << "\";" << "\n";

			for (auto& node : family) {
				dot_file << "\"" << s << "\" -> \"" << node->name() << "\";\n";

			}
		}

		else
			for (auto& node : family) {
				dot_file << "\"" << name() << "\" -> \"" << node->name() << "\";\n";

			}
		
	}
	

	for (auto& family : families) {
		for (auto& node : family) {
			i = 99 * i + 12345;
			node->print_tree_in_dot_format(dot_file, i);
		}

	}
}




